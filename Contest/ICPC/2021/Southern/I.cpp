#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10; 

int n; 
int a[N], pos[N]; 
int bit[N], bitr[N];
long long fl[N], fr[N]; 

void updater(int x) { 
    for (; x <= n; x += x & -x) 
        bitr[x]++; 
}

int getr(int x) { 
    int ret = 0;
    for (; x; x -= x & -x) 
        ret += bitr[x]; 
    return ret; 
}

void update(int x) { 
    for (; x; x -= x & -x) 
        bit[x]++; 
}

int get(int x) { 
    int ret = 0;
    for (; x <= n; x += x & -x) 
        ret += bit[x]; 
    return ret; 
}

int main() { 
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0); 

    cin >> n; 
    for (int i = 1; i <= n; ++i) { 
        cin >> a[i]; 
        pos[a[i]] = i; 
    }

    memset(bit, 0, sizeof(bit)); 
    for (int i = 1; i <= n; ++i) { 
        fl[i] = fl[i - 1] + get(pos[i]); 
        update(pos[i]); 
        // cout << i << " " << fl[i] << endl; 
    }
    // cout << endl; 

    memset(bitr, 0, sizeof(bitr)); 
    for (int i = n; i >= 1; --i) { 
        fr[i] = fr[i + 1] + getr(pos[i]); 
        updater(pos[i]); 
        // cout << i << " " << fr[i] << endl; 
    }
    // cout << endl; 

    long long res = fl[0] + fr[2]; 
    for (int i = 1; i <= n; ++i) { 
        res = min(res, fl[i] + fr[i + 2]); 
        // cout << i << " " << fl[i] + fr[i + 2] << endl; 
    }

    printf("%lld\n", res); 

    return 0; 
}