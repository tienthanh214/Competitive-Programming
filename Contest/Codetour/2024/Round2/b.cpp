#include <iostream>
#include <vector> 
#include <algorithm>

using namespace std;

int main() {
    long long M; cin >> M;
    vector<char> a;
    for (int i = 2; 1ll * i * i <= M; ++i) {
        if (M % i != 0) continue;
        while (M % i == 0) {
            M /= i;
        }
        a.push_back(char(i % 26 + 'A'));
    }
    if (M > 1) {
        a.push_back(char(M % 26 + 'A'));
    
    }
    sort(a.begin(), a.end());
    // a.resize(unique(a.begin(), a.end()) - a.begin());
    for (char c : a) cout << c;
    return 0;
}