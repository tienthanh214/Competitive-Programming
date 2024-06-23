#pragma GCC optimize("O3")

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef unsigned long long ll;

namespace BigNum {
    typedef vector<ll> BigInt;
    const ll base = 1e18;
    const int base_digits = log10(base);

    void Fix(BigInt &a) {
        a.push_back(0);
        for(int i = 0; i < a.size() - 1; ++i) {
            a[i + 1] += a[i] / base;
            a[i] %= base;
            if (a[i] < 0) a[i + 1]--, a[i] += base;
        }
        while (a.size() > 1 && a.back() == 0) a.pop_back();
    }   

     BigInt Convert(const string &s) {
        BigInt a; // convert a string to BigInt
        a.resize(s.size() / base_digits + 1);
        for(int i = 0; i < s.size(); ++i) {
            int x = (s.size() - 1 - i) / base_digits;
            a[x] = a[x] * 10 + s[i] - '0';
        }
        return Fix(a), a;
    }

    void Divide(const BigInt &a, ll x, BigInt &q, __uint128_t &r) {
        q.clear(); r = 0;
        for(int i = a.size() - 1; i >= 0; --i) {
            r = r * base + a[i];
            q.push_back(r / x);
            r %= x;
        }
        reverse(q.begin(), q.end());
        Fix(q);
    }

    ll operator % (const BigInt &a, ll x) {
        if (x > 11) {
            if (x % 2 == 0) return 1;
            if (x % 3 == 0) return 1;
            if (x % 5 == 0) return 1;
            if (x % 7 == 0) return 1;
            if (x % 11 == 0) return 1;
        }

        ll r = 0;
        for(int i = a.size() - 1; i >= 0; --i) {
            r = (__uint128_t(r) * base + a[i]) % x;
        }
        return r;
    }

    BigInt operator / (const BigInt &a, ll x) {
        BigInt q; __uint128_t r;
        Divide(a, x, q, r);
        return q;
    }

    istream& operator >> (istream &cin, BigInt &a) {
        string s; cin >> s; 
        a = Convert(s);
        return cin;
    }
}

using namespace BigNum;

ll getInc(ll x) {
    return 1;
    if (x >= 5) {
        if ((x - 5) % 6 == 0) return 2;
        if ((x - 5) % 6 == 1) return 4;
    }
    return 1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    ll S;
    int K;
    cin >> S >> K;
    BigInt N;
    cin >> N;
    if (S < 2) S = 2;
    while (K > 0) {
        while (N % S != 0) {
            S += getInc(S);
        }
        N = N / S;
        --K;
        cout << S << ' ';
    }
    return 0;
}
