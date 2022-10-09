#include <bits/stdc++.h>
#include <ctime>

#define int long long

using namespace std;

template<typename T> void Write(T n) {
    if (n == 0) {
        putchar('0');
        putchar(' ');
        return;
    }
    char digit[20];
    int k = 0;
    while (n > 0) {
        digit[k++] = n % 10;
        n /= 10;
    }
    for (int i = k - 1; i >= 0; --i)
        putchar(digit[i] + '0');
    putchar(' ');
}

int getTime(const string& x) {
    std::istringstream ss(x);
    std::tm t{};
    ss >> std::get_time(&t, "%Y-%m-%d@%T");
    return mktime(&t);
}

struct Post {
    int id;
    int t;
    int view;
    string state;
    Post(int _id = 0, int _t = 0, int _view = 0, string _state = "") {
        id = _id;
        t = _t;
        view = _view;
        state = _state;
    }
    bool operator < (const Post& other) {
        if (view != other.view)
            return view > other.view;
        return t > other.t;
    }
};

map<int, set<int>> pages, friends, follows;
map<int, vector<Post>> post;
set<pair<int, int>> relative;
set<int> seen;
int idx;
int currentTime;
vector<Post> allPost;

void readInput() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif // LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);// cout.tie(0);
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        string type; cin >> type;

        if (type == "friends") {
            int u, v; cin >> u >> v;
            friends[u].insert(v);
            friends[v].insert(u);
            relative.insert({u, v});
            relative.insert({v, u});
        }
        else if (type == "follow-user") {
            int u, v; cin >> u >> v;
            follows[u].insert(v);
        }
        else if (type == "follow-fanpage") {
            int u, v; cin >> u >> v;
            pages[u].insert(v);
        }
        else if (type == "fanpage-article") {
            int id, u;
            string t;
            int view;
            cin >> id >> u >> t >> view;
            post[u].push_back(Post(id, getTime(t), view));
            allPost.push_back(Post(id, getTime(t), view));
        }
        else if (type == "user-article") {
            int id, u;
            string t;
            int view;
            string state;
            cin >> id >> u >> t >> view >> state;
            post[u].push_back(Post(id, getTime(t), view, state));
            allPost.push_back(Post(id, getTime(t), view, state));
        }
    }
    cin >> idx;
    string timeT; cin >> timeT;
    currentTime = getTime(timeT);
}

bool check7Day(int t1, int t2) {
    if (t1 < t2) return false;
    return (t1 - t2 + 86400 - 1) / 86400 <= 7;
}

void printResult(vector<Post>& res) {
    sort(res.begin(), res.end());
    int i = 0, j = 0;
    while (i < res.size() || j < res.size()) {
        while (i < res.size() && res[i].state == "1")
            ++i;
        if (i < res.size())
            Write(res[i++].id);

        while (j < res.size() && res[j].state == "0")
            ++j;
        if (j < res.size())
            Write(res[j++].id);

    }
    putchar('\n');
}

void solve() {
    set<int> adjPage = pages[idx];
    set<int> adjFollow = follows[idx];
    set<int> adjFriend = friends[idx];
    // --------------- LEVEL 1 ----------------
    vector<Post> level1;
    for (int x: adjPage) {
        for (const Post& p : post[x]) {
            if (p.state != "") continue;
            if (seen.count(p.id)) continue;
            if (check7Day(currentTime, p.t)) {
                level1.push_back(p);
                level1.back().state = "0";
                seen.insert(p.id);
            }
        }
    }
    for (int x : adjFollow) {
        if (!relative.count({x, idx})) continue;
        for (const Post& p : post[x]) {
            if (p.state == "") continue;
            if (seen.count(p.id)) continue;
            if (check7Day(currentTime, p.t)) {
                level1.push_back(p);
                level1.back().state = "1";
                seen.insert(p.id);
            }
        }
    }
    printResult(level1);




    //------------------- LEVEL 2 ------------------
    vector<Post> level2;
    for (const Post& p : allPost) {
        if (p.state == "restricted") continue;
        if (p.view <= 1000) continue;
        if (seen.count(p.id)) continue;
        if (check7Day(currentTime, p.t)) {
            level2.push_back(p);
            level2.back().state = "0";
            seen.insert(p.id);
        }
    }
    for (int x : adjFollow) {
        for (const Post& p: post[x]) {
            if (p.state == "") continue;
            if (p.state == "restricted" && !relative.count({x, idx}))
                continue;
            if (p.view <= 100) continue;
            if (seen.count(p.id)) continue;
            if (check7Day(currentTime, p.t)) {
                level2.push_back(p);
                level2.back().state = "1";
                seen.insert(p.id);
            }
        }
    }
    printResult(level2);




    // --------------- LEVEL 3 -----------------
    vector<Post> level3;
    for (int x : adjFriend) {
        for (const Post&p : post[x]) {
            if (p.state == "") continue;
            if (seen.count(p.id)) continue;
            if (currentTime >= p.t) {
                level3.push_back(p);
                level3.back().state = "0";
                seen.insert(p.id);
            }

        }
    }
    printResult(level3);

}

#undef int

 // danh sach nay co the phan biet
int main() {
    readInput();
    solve();
    // cout << getDiffDay("2020-12-07@06:30:30", "2020-11-30@06:30:30");
    return 0;
}
