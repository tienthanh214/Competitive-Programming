#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int N = 1e5 + 10;

int n;
vector<vector<string>> a;
vector<vector<LL>> hashT;

vector<string> Parse(string& st) {
    st += ' ';
    vector<string> res;
    string cur = "";
    for (int i = 0; i < st.size(); ++i) {
        if (st[i] == ':') {
            res.push_back(cur);
            cur.clear();
            i++;
        } else if (st[i] == ' ') {
            res.push_back(cur);
            cur.clear();
        } else {
            cur += st[i];
        }
    }
    return res;
}

string pattern;
vector<string> A;
vector<int> idx;

bool comp(int x, int y) {
    return a[x][0] < a[y][0];
}

void readInput() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif // LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;

    string st; getline(cin, st);
    for (int i = 0; i < n; ++i) {
        getline(cin, st);
        a.push_back(Parse(st));
        A.push_back(st);
        idx.push_back(i);
    }
    sort(idx.begin(), idx.end(), comp);
    // for (int i = 0; i < n; ++i) cout << A[idx[i]] << endl;
    cin >> pattern;
}

void solve() {
    for (int i = 0; i < n; ++i) {
        int pos = idx[i];
        if (a[pos][0] == pattern) {
            for (int j = i; j < min(n, i + 5); ++j)
                cout << A[idx[j]] << '\n';
            return;
        }
    }
    cout << "no data";
}

int main() {
    readInput();
    solve();
    return 0;
}
