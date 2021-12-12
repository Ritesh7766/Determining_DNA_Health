#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    int lim = atoi(argv[2]);
    int hLim = atoi(argv[3]);
    int s = atoi(argv[4]);
    int sLim = atoi(argv[5]);

    char map[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    ofstream file;
    file.open(argv[6]);

    file << n << "\n";
    for (int i = 0; i < n; i++) {
        int len = rand()%(lim-3 + 1) + 3;
        char word[len]{' '};
        for (int i = 0; i < len - 1; i++) 
            word[i] = map[rand() % 26];
         
        file << word << " ";
    }
    file << "\n";

    for (int i = 0; i < n; i++) {
        int health = rand() % hLim;
        file << health << " ";
    }
    file << "\n";

    file << s << "\n";
    for (int i = 0; i < s; i++) {
        int n1 = rand() % n;
        int n2 = rand() % n;
        int start = (n1 > n2) ? n2 : n1;
        int end = (n1 > n2) ? n1 : n2;
        file << start << " " << end << " ";
        int len = rand()%(sLim-3 + 1) + 3;
        char word[len]{' '};
        for (int i = 0; i < len - 1; i++) 
            word[i] = map[rand() % 26];
        
        if (i == s - 1)
            file << word;
        file << word << "\n";
    }   
    return 0;
}