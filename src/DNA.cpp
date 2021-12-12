#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <chrono>
#include "Trie.cpp"

typedef struct DNA{
    string dna; 
    int start;
    int end;
    DNA(string dna, int start, int end) {
        this->dna = dna;
        this->start = start;
        this->end = end;
    }
}DNA;

int main(int argc, char *argv[]) {
    ifstream inFile(argv[1]);
    int n, s;
    string buffer;
    getline(inFile, buffer);
    n = stoi(buffer);

    getline(inFile, buffer);
    vector<string> genes;
    string gene;
    stringstream ss(buffer);
    while (ss >> gene)
        genes.push_back(gene);

    getline(inFile, buffer);
    vector<unsigned long> healths;
    string health;
    stringstream  ss2(buffer);
    while (ss2 >> health) 
        healths.push_back((unsigned long)stoi(health) );

    getline(inFile, buffer);
    s = stoi(buffer);

    vector<DNA> strands;
    vector<string> str;
    string strand;
    stringstream ss3(buffer);

    for (int i = 0; i < s; i++) {
        getline(inFile, buffer);
        str.push_back(buffer);
    }

    string buf;
    for (string word : str) {
        stringstream temp(word);
        temp >> buf;
        int start = stoi(buf);
        temp >> buf;
        int end = stoi(buf);
        temp >> buf;
        strands.push_back(DNA(buf, start, end) );
    }

    Trie dictionary;
    auto time_start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++)
        dictionary.addWord(genes[i], healths[i]);  
    auto time_end = chrono::high_resolution_clock::now();

    auto load = chrono::duration_cast<chrono::microseconds>(time_end - time_start);
    cout << "Load " << load.count() << endl; 

    auto time_start1 = chrono::high_resolution_clock::now();
    dictionary.createFailureLinks();
    auto time_end1 = chrono::high_resolution_clock::now();

    auto link = chrono::duration_cast<chrono::microseconds>(time_end1 - time_start1);
    cout << "Linker " << link.count() << endl;

    auto time_start2 = chrono::high_resolution_clock::now();
    vector<unsigned long long> S;
    unsigned long long h = 0;
    for (int i = 0; i < s; i++) {
        h = dictionary.analyzeDNA(strands[i].dna, strands[i].start, strands[i].end);
        S.push_back(h);
    }
        
    auto time_end2 = chrono::high_resolution_clock::now();
    auto analyze = chrono::duration_cast<chrono::microseconds>(time_end2 - time_start2);

    cout << "analyze " << analyze.count() << endl;
    sort(S.begin(), S.end() );
    cout << S[0] << " " << S[S.size() - 1] << endl;

    inFile.close();
    return 0;
}