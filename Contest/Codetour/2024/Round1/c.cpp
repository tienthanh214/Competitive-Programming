/*
    - Có thể sử dụng Fenwick Tree kết hợp kỹ thuật nén số để giải ngắn gọn hơn
    - Code ở dưới thì sắp xếp truy vấn lại theo giá trị chèn vào, 
    vì nhận xét số nhỏ chèn vào thì không thay đổi vị trí nữa, nó chỉ ảnh hưởng tới vị trí các số lớn hơn chèn vào sau
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> ii;

class FenwickTree { 
    private:
        int _size;
        vector<int> ft;
    public:
        FenwickTree(int __size = 0) {
            _size = __size;
            ft.resize(_size + 1);
            fill(ft.begin(), ft.end(), 0);
        }
        ~FenwickTree() {ft.clear();};
        void update(int pos, int val) {
            for (int i = pos; i > 0; i -= i & -i)
                ft[i] += val;
        }
        int get(int pos) {
            int ret = 0;
            for (int i = pos; i <= _size; i += i & -i)
                ret += ft[i];
            return ret;
        }
    };

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    vector<ii> query(q);
    vector<int> answer(q);
    for (int i = 0; i < q; ++i) {
        cin >> query[i].first;
        query[i].second = i;
    }   
    int idx = 0;
    int curPos = 1;
    sort(query.begin(), query.end());
    FenwickTree ft(q);
    for (ii x : query) {
        int val = x.first, pos = x.second;
        while (idx < n && a[idx] <= val) {
            ++idx;
            ++curPos;
        }
        answer[pos] = curPos - ft.get(pos + 1);
        ft.update(pos + 1, 1);
        ++curPos;
    }
    for (int x : answer) cout << x << '\n';
    
    return 0;
}