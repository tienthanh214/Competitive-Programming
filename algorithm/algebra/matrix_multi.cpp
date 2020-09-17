#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int base;
ll n;

struct Matrix{
    int d[4][4];
    int n, m;

    Matrix(int n, int m){
        this->n = n;
        this->m = m;
        memset(d, 0, sizeof(d));
    }

    Matrix operator * (const Matrix &a) const{
        int x = n, y = a.m, z = m;
        Matrix c(x, y);

        for (int i = 0; i < x; i++)
            for (int j = 0; j < y; j++)
                for (int k = 0; k < z; k++)
                    c.d[i][j] = (c.d[i][j] + d[i][k] * a.d[k][j]) % base;
        return c;
    }

    Matrix operator ^ (ll k) const{
        if (k == 1) return *this;
        Matrix tmp = (*this) ^ (k / 2);
        if (k & 1) return tmp * tmp * (*this);
        return tmp * tmp;
    }
};

int Cal(ll k){
    Matrix a(3, 3);
    Matrix ret(3, 1);

        a.d[0][0] = a.d[0][1] = a.d[0][2] = 1 % base;
        a.d[1][0] = 1 % base;
        a.d[2][1] = 1 % base;

        ret.d[0][0] = 2 % base; ret.d[1][0] = ret.d[2][0] = 1 % base;

        if (k == 1) return 1 % base;
        if (k == 2) return 2 % base;
        ret = (a ^ (k - 2)) * ret;

        return ret.d[0][0];
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);cout.tie(NULL);

    cin >> n >> base;
    cout << Cal(n);

    return 0;
}
