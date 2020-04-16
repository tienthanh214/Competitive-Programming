#include <iostream>
#include <queue>
#include <vector>
#include <typeinfo>
#include <time.h>
#include <string>
#include <algorithm>

using namespace std;

namespace MyHeap {
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
        BinaryHeap(const vector<T>&); //vector to heap
        BinaryHeap(const BinaryHeap&);//copy
        ~BinaryHeap();

        int size();
        bool empty();
        void upHeap(int);
        void downHeap(int);
        void push(T);
        void pop();
        T top();
    };
    //constructor - destructor
    template<class T, class priority>
    BinaryHeap<T, priority>::BinaryHeap(const priority& comp) {
        _prior = comp;
    }

    template<class T, class priority>
    BinaryHeap<T, priority>::BinaryHeap(const vector<T>& arr) {
        value.clear();
        for (int i = 0; i < arr.size(); i++)
            push(arr[i]);
    }
    
    template<class T, class priority>
    BinaryHeap<T, priority>::BinaryHeap(const BinaryHeap& other) {
        value.clear(); 
        *this = other;
    }
    
    template<class T, class priority>
    BinaryHeap<T, priority>::~BinaryHeap() {
        value.clear();
    }
    // class function
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

    //implement heap operator
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

using namespace MyHeap;

/// TESTING AREA

string testMyHeap() {
    BinaryHeap<int, greater<int>> myHeap;
    priority_queue<int> stlHeap;    
    for (int i = 0; i < 1000; i++) {
        int x = rand() + rand() + rand();
        myHeap.push(x);
        stlHeap.push(x);
    }
    while (myHeap.size()) {
        if (myHeap.top() != stlHeap.top())
            break;
        myHeap.pop();
        stlHeap.pop();
    }    
    if (stlHeap.size()) return "Number of element wrong!";
    return "OK!";
}

int main() {
    BinaryHeap<int> heap;
    vector<int> X{1, 7, 5, 3};
    for (int i = 0; i < 5; i++) heap.push(i);
    BinaryHeap<int> temp(heap);
    while (temp.size()) {
        cout << temp.top() << " ";
        temp.pop();
    }
    cout << endl;
    BinaryHeap<int> tmp(X);
    while (tmp.size()) {
        cout << tmp.top() << " ";
        tmp.pop();
    }
    return 0;
    srand(time(NULL));
    int cnt = 0;
    string ret;
    do {
        ret = testMyHeap();
        cnt++;
        cout << "Test " << cnt << ": " << ret << endl;
    } while (cnt <= 1000 && ret == "OK!");
    return 0;
}