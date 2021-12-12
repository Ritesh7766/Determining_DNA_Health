#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <map>
using namespace std;

class Trie {
    private:
    typedef struct Node {
        struct Node *map[26]{NULL};
        struct Node *failureLink;
        struct Node *dictionaryLink;
        bool EOW;
        std::map<int, unsigned long> index_health;

        Node() {
            failureLink = dictionaryLink = NULL;
            EOW = false;
        }
    }Node;

    Node *root;
    int length;

    public:
    Trie() {
        root = new Node;
        length = 0;
    }

    ~Trie() {
        this->destroy();
        root = NULL;
    }

    bool addWord(string word, unsigned long health) {
        Node *trev = root;
        for (int ch : word) {
            if (trev->map[ch - 97] != NULL) {
                trev = trev->map[ch - 97];
                continue;
            }
            trev->map[ch - 97] = new Node;
            trev = trev->map[ch - 97];
        }
        if (trev->EOW) {
            trev->index_health[length] = health + trev->index_health.rbegin()->second;
            length++;
            return true;
        }
        trev->EOW = true;
        trev->index_health[length] = health;
        length++;
        return true;
    }

    bool search(string word) {
        Node *trev = root;
        for (int ch : word) {
            if (trev->map[ch - 97] == NULL)
                return false;
            trev = trev->map[ch - 97];
        }
        return trev->EOW;
    }
    
    unsigned long long analyzeDNA(string DNA, int start, int end) {
        Node *trev = root;
        unsigned long long totalHealth = 0;
        for (int ch : DNA) {
            while (trev->map[ch - 97] == NULL && trev != root) 
                trev = trev->failureLink;
            if (trev->map[ch - 97] == NULL)
                continue;

            if (trev->map[ch - 97]->EOW)  
                totalHealth += computeHealth(trev->map[ch - 97]->index_health, start, end);
       
            for (Node *iterator = trev->map[ch - 97]->dictionaryLink; iterator != NULL; iterator = iterator->dictionaryLink) 
                totalHealth += computeHealth(iterator->index_health, start, end);
    
            trev = trev->map[ch - 97];
        }
        return totalHealth;
    }

    void createFailureLinks() {
        if (root == NULL)
            return;
        Node *parent = NULL;
        Traverse(make_pair(root, parent) );
        Traverse();
        return;
    }

    private:
    typedef struct node_char {
        pair<Node*, Node*> nodes;
        int ch;

        node_char(pair<Node*, Node*> nodes, char ch) {
            this->nodes = nodes;
            this->ch = ch;
        }
    }node_char;

    void Traverse(pair<Node *, Node*> nodes) {
        if (nodes.first == NULL)
            return;
        queue<node_char> Queue;
        Queue.push(node_char(nodes, -1) );
        while (!Queue.empty() ) {
            Node *current_node = Queue.front().nodes.first;
            createFailureLink(Queue.front() );
            Queue.pop();
            for (int ch = 0; ch < 26; ch++)
                if (current_node->map[ch] != NULL)
                    Queue.push(node_char(make_pair(current_node->map[ch], current_node), ch) );
        }
        return;
    }

    void Traverse() {
        if (root == NULL)
            return;
        stack<Node*> Stack;
        Stack.push(root);
        while (!Stack.empty() ) {
            Node *node = Stack.top();
            createDictionaryLink(node);
            Stack.pop();
            for (Node *child : node->map)
                if (child != NULL)
                    Stack.push(child);
        }
    }

    void createDictionaryLink(Node *node) {
        for (Node *trev = node; trev != root; trev = trev->failureLink)
            if (trev->failureLink->EOW) {
                node->dictionaryLink = trev->failureLink;
                break;
            }
        return;
    }

    void createFailureLink(node_char node_pair) {
        if (node_pair.nodes.first == root) {
            root->failureLink = root;
            return;
        }
        else if (node_pair.nodes.second == root) {
            node_pair.nodes.first->failureLink = root;
            return;
        }
        while (node_pair.nodes.second != root) {
            node_pair.nodes.second = node_pair.nodes.second->failureLink;
            if (node_pair.nodes.second->map[node_pair.ch] != NULL) {
                node_pair.nodes.first->failureLink = node_pair.nodes.second->map[node_pair.ch];
                return;
            }   
        }
        node_pair.nodes.first->failureLink = root;   
        return;
    }

    unsigned long computeHealth(map<int, unsigned long> &test, int &start, int &end) {
        if (test.begin()->first > end)
            return 0;
        if (test.rbegin()->first < start)
            return 0;

        map<int, unsigned long>::iterator lowerBound = test.lower_bound(start);
        map<int, unsigned long>::iterator upperBound = test.upper_bound(end);

        if (lowerBound != test.begin() )
            lowerBound--;
        upperBound--;

        if (test.begin()->first >= start)
            return upperBound->second;

        return upperBound->second - lowerBound->second;
    }

    void destroy() {
        if (root == NULL)
            return;
        stack<Node*> Stack;
        Stack.push(root);
        while (!Stack.empty() ) {
            Node *node = Stack.top();
            Stack.pop();
            for (Node *child : node->map)
                if (child != NULL)
                    Stack.push(child);
            delete node;
        }        
    }
};