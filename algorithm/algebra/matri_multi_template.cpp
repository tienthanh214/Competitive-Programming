#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

struct Matrix
{
    int n, m;
    vector<vector<int>> a;
    Matrix(int _n = 0, int _m = 0)
    {
        n = _n;
        m = _m;
        a.assign(n, vector<int>(m, 0));
    }
    Matrix operator*(const Matrix &other) const
    {
        int x = n, y = other.m, z = m;
        Matrix res(x, y);
        for (int i = 0; i < x; ++i)
            for (int j = 0; j < y; ++j)
                for (int k = 0; k < z; ++k)
                    res.a[i][j] = (res.a[i][j] + 1ll * a[i][k] * other.a[k][j] % MOD) % MOD;
        return res;
    }

    Matrix operator^(int b) const
    {
        bool foo = 1;
        Matrix tmp = *this;
        Matrix ret;
        while (b > 0)
        {
            if (b & 1)
                ret = foo ? tmp : ret * tmp, foo = 0;
            tmp = tmp * tmp;
            b >>= 1;
        }
        return ret;
    }
};

int main()
{
    return 0;
}