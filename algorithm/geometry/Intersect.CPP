#include <bits/stdc++.h>

using namespace std;

struct Point {
    int x, y;
    Point (int _x = 0, int _y = 0) : x(_x), y(_y) {};
    int operator * (const Point &a) const {
        return x * a.y - y * a.x;
    }
    Point operator - (const Point &a) const {
        return Point(x - a.x, y - a.y);
    }
    bool operator > (const Point &a) const {
        return x > a.x || x == a.x && y > a.y;
    }
};

struct Line {
    int a, b, c;
    Line (int _a = 0, int _b = 0, int _c = 0) : a(_a), b(_b), c(_c) {};
};

Point to_vector(Point A, Point B){
    return Point(B.x - A.x, B.y - A.y);
}

Line Extract(Point A, Point B){
    int a = A.y - B.y;
    int b = B.x - A.x;
    int c = -(a * A.x + b * A.y);
    return Line(a, b, c);
}

ostream& operator << (ostream &cout, const Point &a){
    cout << a.x <<  " " << a.y;
    return cout;
}

int main(){
    Line l1, l2;
    Point a, b, c, d, AC, AB, DC;
    int D, Dx, Dy;
    double p, q;
    int TC;

        cin >> TC;
        while (TC--){
            cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
            if (a > b) swap(a, b);
            if (c > d) swap(c, d);
            AC = c - a; AB = b - a; DC = c - d;
            // AC = pAB + qDC
            D = AB * DC; Dx = AC * DC; Dy = AB * AC;
            p = (double)Dx / D; q = (double)Dy / D;

            if (D == 0){
                if (Dx == 0 && Dy == 0){
                    if (a.x <= c.x && c.x <= b.x) cout << "YES";
                    else if(c.x <= a.x && a.x <= d.x) cout << "YES";
                    else cout << "NO";
                }
                else cout << "NO";
            }
            else if (0 <= p && p <= 1 && 0 <= q && q <= 1) cout << "YES";
                 else cout << "NO";
            cout << endl;
        }


    return 0;
}
