#include <iostream>

using namespace std;

int main() {
    int n, k; cin >> n >> k; cout << ((1ll * ((n + k - 1) / k) * ((n + k - 1) / k + 1))) / 2;
    return 0;
}