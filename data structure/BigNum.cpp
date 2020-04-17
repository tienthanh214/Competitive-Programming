#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FOD(i, a, b) for (int i = a; i >= b; i--)
#define REP(i, a, b) for (int i = a; i < b; i++)
#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A, n) { cout << #A << " = "; FOR(_, 1, n) cout << A[_] << " "; cout << endl;}

namespace BigNum {
    typedef long long LL;
    typedef vector <LL> BigInt;
    const LL base = 1E8; // each element store 8 digit 

    void Fix(BigInt &a) {
        a.push_back(0);
        REP(i, 0, a.size() - 1) {
            a[i + 1] += a[i] / base;
            a[i] %= base;
            if (a[i] < 0) a[i + 1]--, a[i] += base;
        }
        while (a.size() > 1 && a.back() == 0) a.pop_back();
    }   

    BigInt Convert(LL x) { // x less than base
        //convert an integer to BigInt
        return BigInt(1, x);
    }

    BigInt Convert(const string &s) {
        BigInt a; // convert a string to BigInt
        a.resize(s.size() / 8 + 1);
        REP(i, 0, s.size()) {
            int x = (s.size() - 1 - i) / 8;
            a[x] = a[x] * 10 + s[i] - '0';
        }
        return Fix(a), a;
    }

    BigInt& operator += (BigInt &a, const BigInt &b) {
        a.resize(max(a.size(), b.size()));
        REP(i, 0, b.size()) a[i] += b[i];
        return Fix(a), a;
    }

    BigInt& operator -= (BigInt &a, const BigInt &b) {
        REP(i, 0, b.size()) a[i] -= b[i];
        return Fix(a), a;
    }

    BigInt operator + (BigInt a, LL b) {
        a += Convert(b); return a;
    }

    BigInt operator - (BigInt a, LL b) {
        a -= Convert(b); return a;
    }

    BigInt operator + (BigInt a, const BigInt &b) {
        a += b; return a;
    }

    BigInt operator - (BigInt a, const BigInt &b) {
        a -= b; return a;
    }

    BigInt operator * (BigInt a, int b) {
        REP(i, 0, a.size()) a[i] *= b;
        return Fix(a), a;
    }

    BigInt operator * (const BigInt &a, const BigInt &b) {
        BigInt c(a.size() + b.size());
        REP(i, 0, a.size()) REP(j, 0, b.size())
            c[i + j] += a[i] * b[j];
        return Fix(c), c;
    }

    void Divide(const BigInt &a, int x, BigInt &q, LL &r) {
        q.clear(); r = 0;
        FOD(i, a.size() - 1, 0) {
            r = r * base + a[i];
            q.push_back(r / x);
            r %= x;
        }
        reverse(q.begin(), q.end());
        Fix(q);
    }

    BigInt operator / (const BigInt &a, int x) {
        BigInt q; LL r;
        Divide(a, x, q, r);
        return q;
    }

    int operator % (const BigInt &a, int x) {
        BigInt q; LL r;
        Divide(a, x, q, r);
        return r;
    }

    bool operator < (const BigInt &a, const BigInt &b) {
        if (a.size() != b.size()) return a.size() < b.size();
        FOD(i, a.size() - 1, 0) if (a[i] != b[i]) return a[i] < b[i];
        return 0;
    }

    istream& operator >> (istream &cin, BigInt &a) {
        string s; cin >> s; 
        a = Convert(s);
        return cin;
    }

    ostream& operator << (ostream &cout, const BigInt &a) {
        printf("%d", a.back());
        FOD(i, a.size() - 2, 0) printf("%08d", a[i]);
        return cout;
    }
}

using namespace BigNum;

int main() {
    BigInt a, b;
    a = Convert("1234567890");
    b = Convert("987654321");
    cout << a + b << endl;
    if (a < b) cout << '-' << b - a << endl;
        else cout << a - b << endl;
    cout << a * b << endl;
    return 0;
}



