#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<string> a;

unordered_map<long long, int> cnt;

void readInput() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        string st; cin >> st;
        a.push_back(st);
    }
}

int checkMatchPattern(int x, int y) {
    int mask = 0;
    if (x + 4 >= n || y + 4 >= m) return -1;
    for (int i = x; i <= x + 4; ++i) {
        for (int j = y; j <= y + 4; ++j) {
            if (i == x || i == x + 4 || j == y || j == y + 4) {
                if (a[i][j] != '#') return -1;
            } else {
                if (a[i][j] == '#') return -1;
                mask |= (a[i][j] == 'o') << ((i - x - 1) * 3 + (j - y - 1));
            }
        }
    }
    return mask;
}

void clearBlock(int x, int y, bool horizontal) {
    for (int i = x; i < x + 4; ++i) {
        a[i][y] = '@';
        if (!horizontal) a[i][y + 4] = '@';
    }
    for (int j = y; j < y + 4; ++j) {
        a[x][j] = '@';
        if (horizontal) a[x + 4][j] = '@';
    }
}

void clearLastBlock(int x, int y) {
    for (int i = x; i <= x + 4; ++i)
        a[i][y] = a[i][y + 4] = '@';
    for (int j = y; j <= y + 4; ++j)
        a[x][j] = a[x + 4][j] = '@';
}

// min rotated
long long getMinShift(const vector<int> curMask) {
    long long minMask = 1e18;
    for (int i = 0; i < curMask.size(); ++i){
        long long cur = 0;
        for (int j = i; j < curMask.size(); ++j)
            cur = cur << 9 | curMask[j];
        for (int j = 0; j < i; ++j)
            cur = cur << 9 | curMask[j];
        minMask = min(minMask, cur);
    }
    return minMask;
}

long long getFeatureMask(const vector<int> curMask) {
    
}

void findAllPattern() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == '@') j += 4;
            int mask = checkMatchPattern(i, j);
            if (mask == -1) continue;
            vector<int> curMask;
            curMask.push_back(mask);
            // check horizontal
            int tempJ = j, tempI = i;
            do {
                int nextMask = checkMatchPattern(tempI, tempJ + 4);
                if (nextMask == -1) break;
                clearBlock(tempI, tempJ, true);
                tempJ += 4;
                curMask.push_back(nextMask);
            } while (true);
            // check vertical
            do {
                int nextMask = checkMatchPattern(tempI + 4, tempJ);
                if (nextMask == -1) break;
                clearBlock(tempI, tempJ, false);
                tempI += 4;
                curMask.push_back(nextMask);
            } while (true);
            clearLastBlock(tempI, tempJ);
            if (tempI > i) { // vertical
                for (int &x : curMask) x = rotate(x);
            }

            


            j = tempJ;
        }
    }
}

int rotate(int mask) {
    int res = 0;
    for (int i = 0; i < 9; ++i) {
        int x = i / 3, y = i % 3;
        res |= (mask >> i & 1) << ((2 - y) * 3 + x);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    readInput();
    // findAllPattern();
    cout << rotate(305);
    return 0;
}