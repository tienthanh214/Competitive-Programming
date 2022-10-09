#include <bits/stdc++.h>
using namespace std;
typedef pair <int, int> ii;

const int N = 1e5 + 10;

int n, k, a[N];

int readInt() {
    char ch;
    int ret = 0;
    for (ch = getchar(); !isdigit(ch); ch = getchar());
    ret = ch - '0';
    for (ch = getchar();  isdigit(ch); ch = getchar())
        ret = ret * 10 + ch - '0';
    return ret;
}

void printInt(int x) {
    if (x == 0) {
        putchar('0');
        return;
    }
    if (x > 9) printInt(x / 10);
    putchar(x % 10 + '0');
}

struct Node{
    int child[2];
    int pa;
    int value;
    Node(){
        child[0] = child[1] = pa = -1;
    }
};

int Root = 0;

Node arr[N * 40];

int cntNode = 0;
int nodeB[N];
int b[N];
map<int, int> cnt;

void update(int indx){
    int p = Root;
    for (int i = 31; i >= 0; --i) {
        int idx = a[indx] >> i & 1;
        if (arr[p].child[idx] == -1) {
            arr[p].child[idx] = ++cntNode;
            arr[cntNode].pa = p;
        }
        p = arr[p].child[idx];
    }
    arr[p].value = a[indx];
    nodeB[indx] = p;
    b[indx] = a[indx];
}

bool findNext(int indx) {
    int p = nodeB[indx];
    for (int i = 0; i <= 31; ++i) {
        p = arr[p].pa;
        int indxA = a[indx] >> i & 1,
            indxB = b[indx] >> i & 1;
        if ((1 ^ indxA ^ indxB) > (indxA ^ indxB) && arr[p].child[1 ^ indxB] != -1) {
//            p = p -> child[1 ^ indxB];
            p = arr[p].child[1^indxB];
            for (int j = i - 1; j >= 0; --j) {
                int idx = a[indx] >> j & 1;
//                if (p -> child[idx])
//                    p = p -> child[idx];
//                else
//                    p = p -> child[1 ^ idx];
                if (arr[p].child[idx] != -1)
                    p = arr[p].child[idx];
                else
                    p = arr[p].child[1 ^ idx];
            }
            break;
        }
        if (i == 31)
            return false;
    }
    nodeB[indx] = p;
    b[indx] = arr[p].value;
    return true;
}

priority_queue<pair<int, int>> st;
int cntPush[N];

void Solve(){
    n = readInt();
    k = readInt();
    for (int i = 0; i < n; ++i) {
//        cin >> a[i];
        a[i] = readInt();
        cnt[a[i]]++;
        update(i);
        st.push({0, i});
        cntPush[i] = 0;
    }
//    for (int i = 0; i < n; ++i) {
//        while (findNext(i)) {
//            cout << i << " " << b[i] << endl;
//        }
//    }
//    int tk = k;
    k *= 2;
    while (k > 0) {
        pair<int, int> PP = st.top();
        st.pop();
        PP.first *= -1;
        int curCnt = cnt[PP.first ^ a[PP.second]] - (PP.first == 0);
        for (; curCnt; --curCnt) {
//            cout << PP.first << " ";
            if (k % 2) {
                printInt(PP.first);
                putchar(' ');
            }
            --k;
            if (k == 0)
                break;
        }
//        cout << "push: " << PP.second << endl;
        cntPush[PP.second]++;
        if (cntPush[PP.second] == n)
            continue;
        if (findNext(PP.second)) {
            st.push({-(b[PP.second] ^ a[PP.second]), PP.second});
        }
    }
//        cout << res[i * 2] << " ";
//    vector<int> temp;
//    for (int i = 0; i < n; ++i)
//        for (int j = i + 1; j < n; ++j)
//            temp.push_back(a[i] ^ a[j]);
//    sort(temp.begin(), temp.end()); cout << endl;
//    for (int i = 0; i < tk; ++i)
//        cout << temp[i] << " ";
}

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }
//    ios_base::sync_with_stdio(0);
//    cin.tie(0); cout.tie(0);
    int testcase = 1;
    // cin >> testcase;
    while (testcase--){
        Solve();
    }

    return 0;
}

