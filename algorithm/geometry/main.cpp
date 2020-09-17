#include <bits/stdc++.h>

using namespace std;

const int MAXN = (int) 1e5 + 5;
const double eps = 1e-6;
const double zero = 0;
#define sqr(x) x * x

/// *********** POINT *********
struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {};
};

Point v0;

double Dist(Point A, Point B) {
    return sqrt(sqr((B.x - A.x)) + sqr((B.y - A.y)));
}

int Dot(Point A, Point B) {
    return A.x * B.x + A.y * B.y;
}

int Cross(Point A, Point B) {
    return A.x * B.y - A.y * B.x;
}

double RadOx(Point A) {
    return atan2(A.y, A.x);
}

double RadTwoVector(Point A, Point B) {// (a1.b1 + a2.b2) / (sqrt(a1^2+a2^2).sqrt(b1^2+b2^2)
    return acos((double) Dot(A, B) / (Dist(A, v0) * Dist(B, v0)));
}


/// *********** LINE **********
struct Line {
    int a, b, c;
    Line (int _a = 0, int _b = 0, int _c = 0) : a(_a), b(_b), c(_c) {};
};

Line Extract(Point A, Point B) { // Phuong trinh duong thang di qua A, B
    int a = A.y - B.y;
    int b = B.x - A.x;
    int c = - (a * A.x + b * A.y);
    return Line(a, b, c);
}

bool CrossLine(Line l1, Line l2) { //Hai duong thang khac phuong ?
    return !(Cross(Point(l1.a, l2.a), Point(l1.b, l2.b)));
}

double DistPointToLine(Point A, Line L) { // |a.x + b.y + c| / sqrt(a^2 + b^2)
    return (double) abs(L.a * A.x + L.b * A.y + L.c) / Dist(Point(L.a, L.b), v0);
}

double RadTwoLine(Line l1, Line l2){ //a1.a2 + b1.b2 / (sqrt(a1^2 + b1^2).(sqrt(a2^2 + b2^2))
    return (double) abs(Dot(Point(l1.a, l1.b), Point(l2.a, l2.b))) /
                        (Dist(Point(l1.a, l1.b), v0) * Dist(Point(l2.a, l2.b), v0));
}

/// ********* Triangle ********
bool IsTriangle(int a, int b, int c){
    return (a + b > c) && (a + c > b) && (b + c > a);
}

double Square(int a, int b, int c){
    double p = (a + b + c) / double(2);
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

double Heigh(int a, int b, int c){// Duong cao tai tuong ung a
    return 2 * Square(a, b, c) / (double)a;
}

double Median(int a, int b, int c) { // trung tuyen tuong ung a
    return sqrt((2 * (b * b + c * c) - a * a) / (double)4);
}

double Bisector(int a, int b, int c) {
    double p = (a + b + c) / double(2);
    return 2 * sqrt(p * (p - a) * b * c) / double(b + c);
}

double RadIns(int a, int b, int c) {
    double p = (a + b + c) / double(2);
    return Square(a, b, c) / p;
}

double RadExt(int a, int b, int c) {
    double p = (a + b + c) / double(2);
    return a * b * c / (4 * Square(a, b, c));
}

int main() {
    Point A, B;
    Line l1, l2;
    int a, b, c;
        //cin >> A.x >> A.y;// >> B.x >> B.y;
        //cin >> l1.a >> l1.b >> l1.c >> l2.a >> l2.b >> l2.c;
        cin >> a >> b >> c;
        printf("%.5f", RadExt(a, b, c));
    return 0;
}
