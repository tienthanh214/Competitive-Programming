#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const double EPS = 1e-10;

struct Point {
    double x, y;
    Point(double _x = 0, double _y = 0) {
        x = _x;
        y = _y;
    }
    Point operator + (const Point &other) {
        return Point(x + other.x, y + other.y);
    }

    Point operator - (const Point &other) {
        return Point(x - other.x, y - other.y);
    }

    double operator * (const Point &other) {
        return x * other.y - y * other.x;
    }

    double distance(const Point &other) {
        double dx = x - other.x;
        double dy = y - other.y;
        return sqrt(dx * dx + dy * dy);
    }

};

struct Line {
    double a, b, c;
    Line(const Point &A, const Point &B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }
};

struct Circle : public Point {
    double r;
    Circle(Point c, double r): Point(c), r(r) {}
};


vector<Point> intersection(const Line &l, const Circle &cir) {
    double r = cir.r, a = l.a, b = l.b;
    double c = l.c + l.a * cir.x + l.b * cir.y;
    vector<Point> res;

    double x0 = -a * c / (a * a + b * b);
    double y0 = -b * c / (a * a + b * b);
    if (c * c > r * r * (a * a + b * b) + EPS)
        return res;
    else if (fabs(c * c - r * r * (a * a + b * b)) < EPS) {
        res.push_back(Point(x0, y0) + Point(cir.x, cir.y));
        return res;
    } else {
        double d = r * r - c * c / (a * a + b * b);
        double mult = sqrt(d / (a * a + b * b));
        double ax, ay, bx, by;
        ax = x0 + b * mult;
        bx = x0 - b * mult;
        ay = y0 - a * mult;
        by = y0 + a * mult;
        res.push_back(Point(ax, ay) + Point(cir.x, cir.y));
        res.push_back(Point(bx, by) + Point(cir.x, cir.y));
        return res;
    }
}

int main() {
    Point A, B, C;
    double r;
    double P;

    cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y >> r >> P;    
    Circle cir(C, r);
    Line l(A, B);
    vector<Point> result = intersection(l, cir);
    for (int i = 0; i < result.size(); ++i) {
        // cerr << "? " << result[i].x << " " << result[i].y << endl;
    }
    if (result.size() != 2) {
        cout << "NO";
    } else {
        // TODO: if diameter 
        double alpha = asin(result[0].distance(result[1]) / 2 / r);
        double total = alpha * r * r;
        double triangle = fabs((result[0] - C) * (result[1] - C) / 2);
        double area = total - triangle;
        double smallerP = (area / (acos(-1) * r * r)) * 100;
        // cerr << smallerP << " " << P << endl;
        // cerr << fixed << setprecision(8) << fabs(P - smallerP) << endl;
        if (fabs(P - smallerP) > 5.0)
            cout << "NO";
        else
            cout << "YES";
        
    }
    return 0;
}