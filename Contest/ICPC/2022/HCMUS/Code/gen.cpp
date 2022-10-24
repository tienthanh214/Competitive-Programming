#include <bits/stdc++.h>
using namespace std;

const string NAME = "H";

const int NTEST = 100;



long long Rand(long long l, long long h) {

    return l + (1LL * rand() * (RAND_MAX + 1) * (RAND_MAX + 1) * (RAND_MAX + 1) +
                1LL * rand() * (RAND_MAX + 1) * (RAND_MAX + 1) +
                1LL * rand() * (RAND_MAX + 1) +
                1ll * rand()) % (h - l + 1);
}

int main()
{
    srand(time(NULL));
    for (int iTest = 1; iTest <= NTEST; iTest++)
    {
        ofstream inp("input.txt");
        int n = 3e5;
        int q = 1e5;
        inp << n << ' ' << q << endl;
        vector<int> p;
        for (int i = 1; i <= n; ++i)
            p.push_back(i);
        random_shuffle(p.begin(), p.end());
        for (int i = 0; i < n; ++i) inp << p[i] << ' ';
        inp << endl;
        for (int i = 0; i < q; ++i) {
            int x = Rand(1, n);
            int y = Rand(1, n);
            inp << x << ' ' << y << endl;
        }
        inp.close();
        system((NAME + ".exe").c_str());
//        system((NAME + "_trau.exe").c_str());
        if (system(
                   "fc answer.txt output.txt") != 0)
        {
            cout << "Test " << iTest << ": WRONG!\n";
            return 0;
        }
        cout << "Test " << iTest << ": CORRECT!\n";
    }
    return 0;
}
