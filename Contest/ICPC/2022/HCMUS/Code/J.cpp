#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef long long lli;

const int N = 2e5 + 10;

char a[10][10];

void Solve(){
    string s;
    cin >> s;
    for (int i = 0; i < s.size(); i++){
        int x = s[i] - '0';
        string bin = "";
        while (x > 0){
            if (x % 2 == 0) bin.push_back('0');
            else bin.push_back('1');
            x /= 2;
        }

        reverse(bin.begin(), bin.end());
        while (bin.size() < 4) bin = "0" + bin;
        //cout << bin << endl;
        for (int j = 0; j < 4; j++) a[j][i] = bin[j];
    }
    for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++) {
            if (a[i][j] == '1') cout << "*";
            else cout << ".";
            if (j < 3)
                cout << " ";
            if (j == 1) cout << "  ";
    }
    if (i < 3) cout << endl;
    }
}

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }
    int testcase = 1;
    // cin >> testcase;
    while (testcase--){
        Solve();
    }

    return 0;
}

