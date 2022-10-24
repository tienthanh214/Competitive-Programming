#include <bits/stdc++.h>
using namespace std;

#define EPS 1e-7

inline int cmp(double a, double b) {
    return (a < b - EPS) ? -1 : ((a > b + EPS) ? 1 : 0);
}

template<typename T>
struct P {
    T x, y;
    P() { x = y = T(0); }
    P(T _x, T _y) : x(_x), y(_y) {}

    P operator + (const P& a) const { return P(x+a.x, y+a.y); }
    P operator - (const P& a) const { return P(x-a.x, y-a.y); }
    P operator * (T k) const { return P(x*k, y*k); }
    P<double> operator / (double k) const { return P(x/k, y/k); }

    T operator * (const P& a) const { return x*a.x + y*a.y; } // dot product
    T operator % (const P& a) const { return x*a.y - y*a.x; } // cross product

    inline T norm() { return x*x + y*y; }

    inline double len() { return sqrt(norm()); }
};
using Point = P<double>;

struct Circle : Point {
    double r;
    Circle(double _x = 0, double _y = 0, double _r = 0): Point(_x, _y), r(_r) {}
    Circle(Point p, double _r) : Point(p), r(_r) {}
};

int ccw(Point a, Point b, Point c) {
    double x = (b - a) % (c - a);
    return cmp(x, 0.0);
}

int cnt = 0;

struct SmallestEnclosingCircle {

    Circle getCircle(vector<Point> points) {
        assert(!points.empty());

        // shuffle(points.begin(), points.end(), std::default_random_engine(123));
        random_shuffle(points.begin(), points.end());
        Circle c(points[0], 0);
        int n = points.size();

        for (int i = 1; i < n; i++)
            if ((points[i] - c).len() > c.r + EPS)
            {
                c = Circle(points[i], 0);
                for (int j = 0; j < i; j++)
                    if ((points[j] - c).len() > c.r + EPS)
                    {
                        c = Circle((points[i] + points[j]) / 2, (points[i] - points[j]).len() / 2);
                        for (int k = 0; k < j; k++)
                            if ((points[k] - c).len() > c.r + EPS)
                                c = getCircumcircle(points[i], points[j], points[k]);
                    }
            }

        return c;
    }

    // NOTE: This code work only when a, b, c are not collinear and no 2 points are same --> DO NOT
    // copy and use in other cases.
    Circle getCircumcircle(Point a, Point b, Point c) {
        assert(ccw(a, b, c));

        double d = 2.0 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
        assert(fabs(d) > EPS);
        double x = (a.norm() * (b.y - c.y) + b.norm() * (c.y - a.y) + c.norm() * (a.y - b.y)) / d;
        double y = (a.norm() * (c.x - b.x) + b.norm() * (a.x - c.x) + c.norm() * (b.x - a.x)) / d;
        Point p(x, y);
        return Circle(p, (p - a).len());
    }
} mec;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    (cout << fixed).precision(10);
    int l; cin >> l;
    vector<Point> p;
    for (int i = 1; i <= l; ++i) {
        for (int j = 1; j <= i; ++j) {
            double x, y; cin >> x >> y;
            p.push_back(Point(x, y));
        }
        Circle res = mec.getCircle(p);
        cout << res.x << ' ' << res.y << ' ' << res.r << '\n';
    }
}
