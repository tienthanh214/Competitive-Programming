#include <bits/stdc++.h>

using namespace std;

int readInt() {
    char ch;
    long long ret = 0;
    bool isNega = false;
    do {
        ch = getchar();
    } while (!isdigit(ch) && ch != '-');
    if (ch == '-') {
        isNega = true;
        ch = getchar();
    }
    do {
        ret = ret * 10 + ch - '0';
    } while (isdigit(ch = getchar()));
    if (isNega) ret = -ret;
    return ret;
}

void printInt(long long x) {
    if (x == 0) {
        putchar('0');
        return;
    }
    bool isNega = false;
    if (x < 0) {
        isNega = true;
        x = -x;
    }
    char digit[20];
    int k = 0;
    while (x > 0) {
        digit[k++] = x % 10 + '0';
        x /= 10;
    }
    if (isNega) putchar('-');
    for (int i = k - 1; i >= 0; --i)
        putchar(digit[i]);
    putchar('\n');
}

const int N = 2e3 + 10; 
const int M = 2e5 + 10; 

int n, m;
int a[N]; 

int nSum = 0; 
int idSum[N * N]; 
pair<int, int> pos[N * N]; 
long long s[N * N]; 

int idQuery[M];
long long res[M];  
tuple<int, int, long long> query[M]; 

long long bit[N][N]; 

void update(int x, int y, long long value) { 
    for (; x; x -= x & -x) { 
        for (int ty = y; ty <= n; ty += ty & -ty) { 
            bit[x][ty] = max(bit[x][ty], value); 
        }
    }
}

long long get(int x, int y) { 
    long long ret = (long long)(-1e15); 
    for (; x <= n; x += x & -x) {
        for (int ty = y; ty; ty -= ty & -ty) { 
            ret = max(ret, bit[x][ty]); 
        }
    }
    return ret; 
}

void solve() {
    memset(bit, -60, sizeof(bit)); 
    n = readInt(); m = readInt();
    for (int i = 1; i <= n; ++i) { 
        a[i] = readInt();
        nSum++; 
        idSum[nSum] = nSum; 
        s[nSum] = a[i]; 
        pos[nSum] = {i, i}; 
        for (int j = i - 1; j >= 1; --j) { 
            nSum++; 
            idSum[nSum] = nSum; 
            s[nSum] = s[nSum - 1] + a[j]; 
            pos[nSum] = {j, i}; 
        }
    }
    sort(idSum + 1, idSum + 1 + nSum, [](const int &x, const int &y) { 
        return s[x] < s[y]; 
    }); 
    for (int i = 1; i <= m; ++i) { 
        auto &[l, r, k] = query[i]; 
        l = readInt();
        r = readInt();
        k = readInt();
    }
    iota(idQuery + 1, idQuery + 1 + m, 1); 
    sort(idQuery + 1, idQuery + 1 + m, [](const int &x, const int &y) { 
        return get<2>(query[x]) < get<2>(query[y]); 
    }); 
    for (int i = 1, j = 1; i <= m; ++i) { 
        int id = idQuery[i]; 
        while (j <= nSum && s[idSum[j]] <= get<2>(query[id])) { 
            update(pos[idSum[j]].first, pos[idSum[j]].second, s[idSum[j]]); 
            j++; 
        }
        res[id] = get(get<0>(query[id]), get<1>(query[id])); 
    }
    for (int i = 1; i <= m; ++i) { 
        if (res[i] == (long long)(-1e15)) 
            puts("NONE"); 
        else 
            printInt(res[i]);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int testCase = 1;
    // cin >> testCase;
    while (testCase--) {
        solve();
    }

    return 0;
}