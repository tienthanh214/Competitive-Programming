#include <bits/stdc++.h>

using namespace std;
typedef pair <int, int> ii;
const int N = 1e5 + 10;
int n, m, k;
vector <int> A[N];
vector <ii> B[N];

int d[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++){
        int u, v;
        cin >> u >> v;
        A[u].push_back(v);
        A[v].push_back(u);
    }
    cin >> k;
    for (int i = 1; i <= k; i++){
        int u, v, t;
        cin >> t >> u >> v;
        B[u].push_back({v, t});
        B[v].push_back({u, t});
    }
//    return 0
    priority_queue<ii, vector<ii>, greater<ii> > PQ;
    for (int i = 1; i <= n; i++) d[i] = 1e9 + 1e7;
    d[1] = 0;
    PQ.push(make_pair(0, 1));
    while (PQ.size()){
        int u = PQ.top().second;
        int du = PQ.top().first;
        PQ.pop();
        if (du > d[u]) continue;
        cout << u << " " << du << endl;
        for (int v: A[u]) if (d[v] > du + 1){
            d[v] = du + 1;
            PQ.push(make_pair(d[v], v));
        }
//        for (ii e: B[u]){
//            int v = e.first;
//            int t = e.second;
//            if (d[v] > t){
//                d[v] = t;
//                PQ.push({d[v], v});
//            }
//        }
    }
    if (d[n] == 1e9 + 1e7) cout << -1 << endl;
    else cout << d[n] << endl;
    return 0;
}
/*
5 4
1 2
3 4
2 3
5 4
1
3 2 5
*/
