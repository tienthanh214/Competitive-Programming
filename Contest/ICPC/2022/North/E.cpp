#include <bits/stdc++.h>
using namespace std;


struct BigInt {
    static const int BASE_DIGITS = 9;
    static const int BASE = 1E9;
    int sign;
    vector<int> a;

    BigInt(): sign(1) {}
    BigInt(long long v) {*this = v;}
    BigInt& operator = (long long v) {
        sign = 1;
        if (v < 0) {
            sign = -1;
            v = -v;
        }
        a.clear();
        for (; v > 0; v = v / BASE)
            a.push_back(v % BASE);
        return *this;
    }
    friend ostream& operator << (ostream &stream, BigInt &v) {
        if (v.sign == -1 && v.a.size() > 0) {
            stream << '-';
        }
        stream << (v.a.empty() ? 0 : v.a.back());
        for (int i = v.a.size() - 2; i >= 0; --i)
            stream << setw(BASE_DIGITS) << setfill('0') << v.a[i];
        return stream;
    }

    void __internal_add(const BigInt &v) {
        if (a.size() < v.a.size()) {
            a.resize(v.a.size(), 0);
        }
        for (int i = 0, carry = 0; i < (int)max(a.size(), v.a.size()) || carry; ++i) {
            if (i == (int)a.size()) a.push_back(0);

            a[i] += carry + (i < (int)v.a.size() ? v.a[i] : 0);
            carry = a[i] >= BASE;
            if (carry) a[i] -= BASE;
        }
    }

    void __internal_sub(const BigInt &v) {
        for (int i = 0, carry = 0; i < (int)v.a.size() || carry; ++i) {
            a[i] -= carry + (i < (int)v.a.size() ? v.a[i] : 0);
            carry = a[i] < 0;
            if (carry) a[i] += BASE;
        }
        while (a.size() > 0 && a.back() == 0) a.pop_back();
    }

    BigInt operator += (const BigInt& v) {
        __internal_add(v);
        return *this;
    }

    BigInt operator -= (const BigInt& v) {
        __internal_sub(v);
        return *this;
    }

    BigInt power(int k) {
        if (k == 0) return BigInt(1);
        for (int i = 1; i < k; ++i) {
            *this += *this;
        }
        return *this;
    }
};


void Calc(int p, int q, BigInt &n){
    if (p == 1){
        if (q == 1) n = BigInt(0);
        else {
            // n = power(2, q - 1) - 1;
            n = BigInt(2).power(q - 1);
            n -= BigInt(1);
        }
    }
    else if (p > q){
        Calc(p - q, q, n);
        // n = (n + 1) * 2;
        n += BigInt(1);
        n += n;
    }
    else if (p < q){
        Calc(p, q - p, n);
        // n = 2 * n + 1;
        n += n;
        n += BigInt(1);
    }
    else {
        cout << "Wrong!\n";
    }
}

void Solve(int p, int q){
    int d = __gcd(p, q);
    p /= d;
    q /= d;
    BigInt n(-1);
    if (p == q){
        cout << 0 << endl;
        return;
    }
    Calc(p, q, n);
    if (n.sign < 0){
        n = -1;
    }

    cout << n << endl;

}


int main() {
     ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }
    BigInt temp = (BigInt(2).power(2));
    //cout << temp << endl;

    int p, q;
    while (cin >> p >> q){
        Solve(p, q);
    }

    return 0;
}
