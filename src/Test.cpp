#include <iostream>
#include <algorithm>
#include <set>
#include "Trie.cpp"

int main(void) {
    Trie aho_corasik_atomaton;
    int n; 
    cin >> n;
    
    vector<string> genes(n);
    for (int i = 0; i < n; i++)
        cin >> genes[i];
    
    vector<unsigned int> healths(n);
    for (int i = 0; i < n; i++) 
        cin >> healths[i];
    for (int i = 0; i < n; i++)
        aho_corasik_atomaton.addWord(genes[i], healths[i]);
    
    aho_corasik_atomaton.createFailureLinks();
    int s, start, end;
    cin >> s;

    vector<string> dnaStrands(s);
    vector<unsigned long long> healthSums;
    for (int i = 0; i < s; i++) {
        cin >> start >> end >> dnaStrands[i];
        unsigned long long h = aho_corasik_atomaton.analyzeDNA(dnaStrands[i], start, end);
        healthSums.push_back(h);
    }
    sort(healthSums.begin(), healthSums.end() );
    cout << healthSums[0] << " " << healthSums[healthSums.size() - 1] << endl;
    
    return 0;   
}