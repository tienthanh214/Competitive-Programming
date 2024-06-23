#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x, index;
    int type; // 0: query open, 1: open, 2: query close, 3: close
    Point(int x, int type, int index) : x(x), type(type), index(index) {}
    bool operator<(const Point &p) const {
        if (x != p.x) return x < p.x;
        return type < p.type;
    }  
};

const int N = 1e5 * 4 + 10;

struct Node {
    int left, right, key;
    Node (int _key = 0, int _left = 0, int _right = 0) {
        this->key = _key;
        this->left = _left; this->right = _right;
    }
};

struct PersistentSegmentTree {
    int id;
    vector<int> ver;
    vector<Node> It;
    int n;

    PersistentSegmentTree(int n) {
        this->id = 0;
        this->n = n;
        ver.resize(N + 1);
        It.resize(21 * N);
        ver[0] = 0;
    }

    int Update(int l, int r, int i, int val, int pre) {
        int cur = ++id;
        if (l == r) {
            It[cur].key = It[pre].key + val;
            return cur;
        }
        int mid = (l + r) >> 1;
        if (i <= mid) {
            It[cur].left = Update(l, mid, i, val, It[pre].left);
            It[cur].right = It[pre].right;
        } else {
            It[cur].left = It[pre].left;
            It[cur].right = Update(mid + 1, r, i, val, It[pre].right);
        }
        It[cur].key = It[It[cur].left].key + It[It[cur].right].key;
        return cur;
    }

    int countNotLess(int l, int r, int val, int pre, int cur) {
        if (l > r || r < val) return 0;
        if (val <= l) {
            int cnt = It[cur].key - It[pre].key;
            return cnt;
        }
        int mid = (l + r) >> 1;
        return countNotLess(l, mid, val, It[pre].left, It[cur].left)
                + countNotLess(mid + 1, r, val, It[pre].right, It[cur].right);
    }

    int countNotLess(int l, int r, int val) {
        if (l > r) return 0;
        return countNotLess(0, n - 1, val, ver[l], ver[r]);
    }

    int update(int i, int val, int pre) {
        return Update(0, n - 1, i, val, pre);
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n, m; cin >> n >> m;
    vector<pair<int, int>> a(n), b(m);
    vector<int> zip;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        zip.push_back(a[i].first);
        zip.push_back(a[i].second);
    }
    for (int i = 0; i < m; ++i) {
        cin >> b[i].first >> b[i].second;
        zip.push_back(b[i].first);
        zip.push_back(b[i].second);
    }
    // compress
    sort(zip.begin(), zip.end());
    zip.resize(unique(zip.begin(), zip.end()) - zip.begin());
    
    PersistentSegmentTree PST(zip.size());
    vector<Point> events;
    vector<int> lastVer(zip.size());
    vector<int> firstVer(zip.size());
    for (int i = 0; i < n; ++i) {
        a[i].first = lower_bound(zip.begin(), zip.end(), a[i].first) - zip.begin();
        a[i].second = lower_bound(zip.begin(), zip.end(), a[i].second) - zip.begin();
        if (a[i].first > a[i].second) swap(a[i].first, a[i].second);   
        // events.push_back(Point(a[i].first, 1, i));
        events.push_back(Point(a[i].second, 0, i));
    }
    for (int i = 0; i < m; ++i) {
        b[i].first = lower_bound(zip.begin(), zip.end(), b[i].first) - zip.begin();
        b[i].second = lower_bound(zip.begin(), zip.end(), b[i].second) - zip.begin();
        if (b[i].first > b[i].second) swap(b[i].first, b[i].second);
        // events.push_back(Point(b[i].first, 0, i));
        events.push_back(Point(b[i].second, 1, i));
    }
    sort(events.begin(), events.end());
    int nVer = 0;
    int ans = 0;
    for (int i = 0; i < events.size(); ++i) {
        if (events[i].type == 0) {
            PST.ver[nVer + 1] = PST.update(a[events[i].index].first, 1, PST.ver[nVer]);
            if (firstVer[a[events[i].index].second] == 0) {
                firstVer[a[events[i].index].second] = nVer;
            }
            ++nVer;
        } else {
            int cnt = PST.countNotLess(firstVer[b[events[i].index].first], nVer, b[events[i].index].first);
            ans = max(ans, cnt);
        }
    }
    cout << ans;
    
    return 0;
}