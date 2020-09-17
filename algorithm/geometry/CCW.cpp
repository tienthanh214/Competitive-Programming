#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-6;

struct point {
    int x, y;
    point(int _x = 0, int _y = 0) {
        this->x = _x;
        this->y = _y;
    }
};

ostream& operator << (ostream& cout, const point &a) {
        cout << a.x << " " << a.y;
        return cout;
}

point to_vector(point a, point b) {
    return point(b.x - a.x, b.y - a.y);
}

int dot (point a, point b) {
    return (a.x * b.x + a.y * b.y);
}

int cross (point a, point b) {
    return a.x * b.y - a.y * b.x;
}

int CCW(point A, point B, point C) {
    int s = cross(to_vector(A, B), to_vector(B, C));
    return (s > 0) ? 1 : (s == 0 ? 0 : -1);
}

bool Online(point A, point B, point C) {
    return (CCW(A, B, C) == 0 && dot(to_vector(A, B), to_vector(B, C)) < 0);
}

int main(){
    point A, B, C;
    point AB, BC;

        cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;
        int s = CCW(A, B, C);
        if (s == 0) puts("Thang Hang");
        if (s > 0) puts("Re trai");
        if (s < 0) puts("Re phai");
        puts("");
        cout << Online(A, B, C);
    return 0;
}
