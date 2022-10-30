#include <bits/stdc++.h>

using namespace std;

const string COLORS[] = {
    "White",
    "Silver",
    "Gray",
    "Black",
    "Red",
    "Maroon",
    "Yellow",
    "Olive",
    "Lime",
    "Green",
    "Aqua",
    "Teal",
    "Blue",
    "Navy",
    "Fuchsia",
    "Purple"
};

const int place[][3] = {
    {255, 255, 255},
    {192, 192, 192},
    {128, 128, 128},
    {0, 0, 0},
    {255, 0, 0},
    {128, 0, 0},
    {255, 255, 0},
    {128, 128, 0},
    {0, 255, 0},
    {0, 128, 0},
    {0, 255, 255},
    {0, 128, 128},
    {0, 0, 255},
    {0, 0, 128},
    {255, 0, 255},
    {128, 0, 128}
};

int sqr(int x) {
    return x * x;
}

int dist(int x, int y, int z, int idx) {
    return sqr(x - place[idx][0]) + sqr(y - place[idx][1]) + sqr(z - place[idx][2]);
}


int main() { 
    int x, y, z;
    while (cin >> x >> y >> z) {
        if (x == -1 && y == -1 && z == -1) break;
        int minDist = 1e9;
        string ans;
        for (int i = 0; i < 16; ++i) {
            if (minDist > dist(x, y, z, i)) {
                minDist = dist(x, y, z, i);
                ans = COLORS[i];
            }
        }
        cout << ans << '\n';
    }


    return 0; 
}