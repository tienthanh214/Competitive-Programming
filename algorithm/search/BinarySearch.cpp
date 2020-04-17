#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

int n;
int *a;

int binarySearch(int x) {
    int l = 0, h = n - 1;
    while (l <= h) {
        int mid = (l + h) >> 1;
        if (a[mid] == x) return mid;
        if (a[mid] < x) l = mid + 1;
            else h = mid - 1;
    }
    return -1;
}

int leftSearch(int x) { //maximum value not greater than x (<= x)
    int l = 0, h = n - 1;
    int ret = -1;
    while (l <= h) {
        int mid = (l + h) >> 1;
        if (a[mid] <= x) {
            ret = mid;
            l = mid + 1;
        } else h = mid - 1;
    }
    return ret;
}

int rightSearch(int x) { //minimum value not less than x (>= x)
    int l = 0, h = n - 1;
    int ret = -1;
    while (l <= h) {
        int mid = (l + h) >> 1;
        if (a[mid] >= x) {
            ret = mid;
            h = mid - 1;
        } else l = mid + 1;
    }
    return ret;
}

int main() {
    n = 5;
    a = new int[n];
    a[0] = 1; a[1] = 5; a[2] = 7; a[3] = 9; a[4] = 12;
    sort(a, a + n);
    cout << binarySearch(5) << endl;
    cout << leftSearch(6) << " " << (*upper_bound(a, a + n, 7)) << endl;
    cout << rightSearch(9) << " " << lower_bound(a, a + n, 9) - a << endl;
    return 0;
}
