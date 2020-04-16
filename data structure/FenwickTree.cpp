#include <iostream>
#include <vector>

using namespace std;

namespace MyFenwickTree {
    template<typename T> 
    class FenwickTree { 
    /// represents Fenwick tree (Binary index tree)
    /// manager sum, get 1 -> pos.
    private:
        int _size;
        vector<T> ft;
    public:
        FenwickTree(int __size = 0) {
            _size = __size;
            ft.resize(_size + 1);
            fill(ft.begin(), ft.end(), 0);
        }
        ~FenwickTree() {ft.clear();};
        void update(int pos, T val) {
            for (int i = pos; i <= _size; i += i & -i)
                ft[i] += val;
        }
        T get(int pos) {
            T ret = 0;
            for (int i = pos; i > 0; i -= i & -i)
                ret += ft[i];
            return ret;
        }
    };
}

using namespace MyFenwickTree;

int main() {
    FenwickTree<int> temp(5);
    temp.update(1, 3);
    temp.update(3, -2);
    cout << temp.get(3) << " " << temp.get(1) << endl;
    return 0;
}