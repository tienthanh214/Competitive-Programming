#include <iostream>
#include <stdio.h>
#include <string>
 
using namespace std;
 
namespace MyTrie {
    static const int ALPHA_SIZE = 256; // ascii
    struct Node {
        int numberOfWord;
        int numberOfPrefix;
        Node* child[ALPHA_SIZE];
        Node() {
            numberOfWord = 0;
            numberOfPrefix = 0;
            for (int i = 0; i < ALPHA_SIZE; i++)
                child[i] = NULL;
        }
        ~Node() {
            for (int i = 0; i < ALPHA_SIZE; i++)
                delete child[i], child[i] = NULL;
        }
    };
    
    class Trie {
    private:
        Node* root;
    public:
        Trie();
        ~Trie();
        void insert(string); //insert new word to trie
        bool remove(string); //remove a word if it appear in trie
        int search(string, bool); //search for a string mode word/prefix 0/1
    };
 
    Trie::Trie() {root = new Node();}
    Trie::~Trie() {delete root; root = NULL;}
 
    void Trie::insert(string str) {
        Node* p = root;
        for (int i = 0; i < str.size(); i++) {
            if (p->child[str[i]] == NULL) 
                p->child[str[i]] = new Node();
            p = p->child[str[i]];
            p->numberOfPrefix++;
        }
        p->numberOfWord++;
    }
 
    int Trie::search(string str, bool prefix = 0) {
        Node* p = root;
        for (int i = 0; i < str.size(); i++) {
            if (p->child[str[i]] == NULL)
                return 0;
            p = p->child[str[i]];
        }
        return prefix ? p->numberOfPrefix : p->numberOfWord;
    }
 
    bool Trie::remove(string str) {
        Node* p = root;
        if (!search(str)) return 0;
        for (int i = 0; i < str.size(); i++) {
            p = p->child[str[i]];
            p->numberOfPrefix--;
        }
        p->numberOfWord--;
        return true;
    }
}
 
using namespace MyTrie;
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    Trie trie; 
    for (int i = 0; i < n; i++) {
        string st; cin >> st;
        trie.insert(st);
    }
    for (int i = 0; i < m; i++) {
        string st; cin >> st;
        cout << trie.search(st, true) << '\n';
    }
    return 0;
}