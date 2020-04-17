#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

namespace JugHeap {
    template<class T, class priority = std::less<T>> //min-heap default
    class BinaryHeap { 
    private:
        vector<T> value;
        priority _prior;
        int left(const int&);
        int right(const int&);
    public:
        BinaryHeap() {};
        BinaryHeap(const priority&);
        ~BinaryHeap();
        int size();
        bool empty();
        void upHeap(int);
        void downHeap(int);
        void push(T);
        void pop();
        T top();
    };

    template<class T, class priority>
    BinaryHeap<T, priority>::BinaryHeap(const priority& comp) {
        _prior = comp;
    }

    template<class T, class priority>
    BinaryHeap<T, priority>::~BinaryHeap() {
        value.clear();
    }
    template<class T, class priority>
    inline int BinaryHeap<T, priority>::size() {
        return value.size();
    }

    template<class T, class priority>
    inline bool BinaryHeap<T, priority>::empty() {
        return value.empty();
    }

    template<class T, class priority>
    inline int BinaryHeap<T, priority>::left(const int &idx) {
        int l = (idx << 1) + 1;
        return l < size() ? l : -1;
    }

    template<class T, class priority>
    inline int BinaryHeap<T, priority>::right(const int &idx) {
        int r = (idx << 1) + 2;
        return r < size() ? r : -1;
    }

    template<class T, class priority>
    void BinaryHeap<T, priority>::upHeap(int pos) {
        while (pos && _prior(value[pos], value[(pos - 1) >> 1])) {
            swap(value[pos], value[(pos - 1) >> 1]); //push pos up
            pos = (pos - 1) >> 1;
        }
    }

    template<class T, class priority>
    void BinaryHeap<T, priority>::downHeap(int pos) {
        while (left(pos) != -1) {
            int child = left(pos);
            if (right(pos) != -1 && _prior(value[right(pos)], value[left(pos)]))
                child++;
            if (_prior(value[pos], value[child])) break;
            swap(value[pos], value[child]); //push pos down to child
            pos = child;
        }
    }

    template<class T, class priority>
    void BinaryHeap<T, priority>::push(T key) {
        value.push_back(key);
        this->upHeap(size() - 1);
    }

    template<class T, class priority>
    T BinaryHeap<T, priority>::top() {
        if (this->empty()) throw "This heap empty!";
        return value[0];
    }

    template<class T, class priority>
    void BinaryHeap<T, priority>::pop() {
        if (this->empty()) throw "This heap empty!";
        value[0] = value.back();
        value.pop_back();
        if (!value.empty()) downHeap(0);
    }
}

using namespace JugHeap;

typedef long long LL;
typedef pair<LL, int> II;

const LL INF = 1e15;
const int N = 1e5 + 10;

int n, m;
LL dist[N];
int trace[N];
vector<II> adj[N];

void readInput() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v, w; 
        scanf("%d%d%d", &u, &v, &w);
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }
}

void Dijkstra(int start, int finish) {
    BinaryHeap<II> heap;
    for (int i = 1; i <= n; i++)
        dist[i] = INF;
    dist[start] = 0;
    heap.push({dist[1], 1});
    while (!heap.empty()) {
        int u = heap.top().second;
        LL du = heap.top().first;
        heap.pop();
        if (du != dist[u]) continue;
        if (u == finish) break; 
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].second;
            int w = adj[u][i].first;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                trace[v] = u;
                heap.push({dist[v], v});
            }
        }
    }
}

void Trace(int u) {
    if (!u) return;
    Trace(trace[u]);
    printf("%d ", u);
}

int main() {
    readInput();
    Dijkstra(1, n);
    if (dist[n] < INF) Trace(n);
    else puts("-1");
    return 0;
}
