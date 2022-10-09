#include <bits/stdc++.h>

using namespace std;

int main() {
    // srand(time(NULL));
    // freopen("input.txt", "r", stdin);
    int n;
    cin >> n;
    vector<int> a(n);

    for (int i = 0; i < n; ++i)
       cin >> a[i];

    vector<int> DQ;
    long long res = 0;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; ++i) {
        while (DQ.size() && a[i] > a[DQ.back()])
            DQ.pop_back();
        l[i] = DQ.empty() ? 0 : DQ.back() + 1;
        DQ.push_back(i);
    }
    DQ.clear();
    for (int i = n - 1; i >= 0; --i) {
        while (DQ.size() && a[i] > a[DQ.back()])
            DQ.pop_back();
        r[i] = DQ.empty() ? n - 1 : DQ.back() - 1;
        DQ.push_back(i);
    }
    for (int i = 0; i < n; ++i) {
        if (l[i] > 0)
            res++;
        if (r[i] < n - 1)
            res++;
    }
    cout << res << endl;
//    res = 0;
//    for (int i = 0; i < n; ++i) {
//        for (int j = i + 1; j < n; ++j) {
//            bool check = true;
//            for (int k = i + 1; k < j; ++k)
//                if (a[k] > a[i] || a[k] > a[j])
//                    check = false;
//            res += check;
//        }
//    }
//    cout << res << endl;

    return 0;
}
