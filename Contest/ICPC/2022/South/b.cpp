#include <bits/stdc++.h>

using namespace std;
typedef pair <int, int> ii;
typedef pair <int, ii> iii;

const int N = 1e3 + 10 ;

int n, m, q;
int type[200005];
iii Query[200005];

vector <ii> A[N];
iii Edge[200005];

vector <int> pos;

set <ii, greater<ii>> curEdge;

struct DSU {
    int Root[N], Ranked[N];
    void Init(int __n){
        for (int i = 1; i <= __n; i++) {
            Root[i] = i;
            Ranked[i] = 1;
        }
    }

    int findRoot(int u) { 
        if (Root[u] == u) return u;
        return Root[u] = findRoot(Root[u]);
    }

    bool join(int u, int v) { 
        u = findRoot(u);
        v = findRoot(v);
        if (u == v) return false;
        if (Ranked[u] > Ranked[v]) swap(u, v);
        Ranked[v] += Ranked[u];
        Root[u] = v;
        return true;
    }
    bool matched(int u, int v){
        return findRoot(u) == findRoot(v);
    }
} DSU;
bool ans[N];
void offCalc(int l, int r){
    if (l > r) return;
    vector <ii> newQuery;
    for(int i = l; i <= r; i++) newQuery.push_back(ii(Query[i].first, i));
    sort(newQuery.begin(), newQuery.end(), greater<ii>());
    DSU.Init(n);
    int Pointer = 0;
    for (set <ii>::iterator it = curEdge.begin(); it != curEdge.end(); ++it) { 
        int w = (*it).first, edgeID = (*it).second;
        while (Pointer < newQuery.size() && newQuery[Pointer].first > w){
            int qID = newQuery[Pointer].second;
            int u = Query[qID].second.first;
            int v = Query[qID].second.second;
            if (DSU.matched(u, v)) ans[qID] = true;
            Pointer++;
        }
        int u = Edge[edgeID].second.first;
        int v = Edge[edgeID].second.second;
        DSU.join(u, v);
    }
    while (Pointer < newQuery.size()){
            int qID = newQuery[Pointer].second;
            int u = Query[qID].second.first;
            int v = Query[qID].second.second;
            if (DSU.matched(u, v)) ans[qID] = true;
            Pointer++;
        }
    cout << l << " " << r << endl;
    for (int i = l; i <= r; i++) if (ans[i]) cout << "YES\n";
    else cout << "NO\n";
}

void Solve(){
    memset(ans, 0, sizeof(ans));
    for (int i = 1; i <= m; i++) curEdge.insert(ii(Edge[i].first, i));
    offCalc(1, pos[0] - 1);
    for (int i = 0; i < pos.size() - 1; i++){
        int id = pos[i];
        int edgeID = Query[id].second.first;
        int edgeW = Edge[edgeID].first;
        ii ed = ii(edgeW, edgeID);
        ii newEd = ii(Query[id].first, edgeID);
        curEdge.erase(ed);
        curEdge.insert(newEd);
        offCalc(pos[i] + 1, pos[i + 1] - 1);
    }
    cout << "hello\n";
   

}

int main() { 
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++){
        int u, v, z;
        cin >> u >> v >> z;
        A[u].push_back(ii(v, i));
        //A[v].push_back(ii(u, i));
        Edge[i] = iii(z, ii(u, v));
    }
    for (int i = 1; i <= q; i++){
        char ch; cin >> ch;
        int a, b, w;
        cin >> a >> b;
        if (ch == 'C'){
            Query[i] = iii(0, ii(a, b));
            pos.push_back(i);
        }
        else{
            cin >> w;
            Query[i] = iii(w, ii(a, b));
        }
    }

    pos.push_back(q + 1);
    Solve();
    return 0; 
}