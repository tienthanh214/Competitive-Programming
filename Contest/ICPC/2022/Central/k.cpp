#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 10; 

int n, m, k; 
int a[N][N]; 
vector<int> coor_x, coor_y; 
vector<int> rect[4]; 

int main() { 
    cin >> n >> m >> k; 
    for (int i = 1; i <= k; ++i) { 
        int x1, y1, w, h; 
        cin >> x1 >> y1 >> w >> h; 
        rect[0].push_back(x1); 
        rect[1].push_back(y1); 
        rect[2].push_back(x1 + w); 
        rect[3].push_back(y1 + h); 
        coor_x.push_back(rect[0].back()); 
        coor_x.push_back(rect[0].back() - 1);
        coor_x.push_back(rect[2].back()); 
        coor_x.push_back(rect[2].back() + 1); 
        coor_y.push_back(rect[1].back()); 
        coor_y.push_back(rect[1].back() - 1); 
        coor_y.push_back(rect[3].back()); 
        coor_y.push_back(rect[3].back() + 1); 
    }
    sort(coor_x.begin(), coor_x.end()); 
    coor_x.resize(unique(coor_x.begin(), coor_x.end()) - coor_x.begin()); 
    sort(coor_y.begin(), coor_y.end()); 
    coor_y.resize(unique(coor_y.begin(), coor_y.end()) - coor_y.begin()); 
    int newN = coor_x.size(), 
        newM = coor_y.size(); 
    coor_x.push_back(coor_x.back() + 1); 
    coor_y.push_back(coor_y.back() + 1); 
    for (int iQ = 0; iQ < k; ++iQ) { 
        for (int i = 1; i <= newN; ++i) 
            for (int j = 1; j <= newM; ++j) { 
                // cout << rect[0][iQ] << " " << coor_x[i - 1] << endl; 
                // cout << rect[2][iQ] << " " << coor_x[j - 1] << endl; 
                // cout << rect[1][iQ] << " " << coor_y[i - 1] << endl; 
                // cout << rect[3][iQ] << " " << coor_y[j - 1] << endl; 
                if (rect[0][iQ] <= coor_x[i - 1] && coor_x[i] - 1 <= rect[2][iQ] && 
                    rect[1][iQ] <= coor_y[j - 1] && coor_y[j] - 1 <= rect[3][iQ]) { 
                        // cout << "add: " << iQ << " " << i << " " << j << endl; 
                        a[i][j]++; a[i + 1][j + 1]++; 
                        a[i + 1][j]--; a[i][j + 1]--;
                    }
            }
    }
    // cout << endl; 
    for (int i = 1; i <= newN; ++i) { 
        for (int j = 1; j <= newM; ++j) { 
            a[i][j] = a[i][j] + a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1]; 
            // cout << a[i][j] << " "; 
        }
        // cout << endl; 
    }
    // cout << endl; 
    long long res0 = 0, res1 = -1, res2 = -1; 
    for (int i = 1; i <= newN; ++i) 
        for (int j = 1; j <= newM; ++j) 
            if (a[i][j] % 2) { 
                res0 += 1ll * (coor_x[i] - coor_x[i - 1]) * (coor_y[j] - coor_y[j - 1]); 
                if (res1 == -1 || res1 > 1ll * coor_y[j - 1] * (n + 1) + coor_x[i - 1])
                    res1 = 1ll * coor_y[j - 1] * (n + 1) + coor_x[i - 1];
                if (res2 == -1 || res2 < 1ll * (coor_y[j] - 1) * (n + 1) + (coor_x[i] - 1))
                    res2 = 1ll * (coor_y[j] - 1) * (n + 1) + (coor_x[i] - 1);
            }
    cout << res0 << " " << res1 << " " << res2 << endl; 

    return 0; 
}