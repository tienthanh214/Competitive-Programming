class Solution {
public:
    typedef long double LD;
    typedef long long LL;
    typedef pair<int, int> Point;
    #define fs first
    #define sc second
    
    int sqr(int x) {return x * x;}
    
    int Cross(Point A, Point B) {
        return A.fs * B.sc - A.sc * B.fs;
    }
   

    LD Dist(Point A, Point B, Point C) {
        int x = sqr(B.fs - A.fs) + sqr(B.sc - A.sc);
        int y = sqr(C.fs - A.fs) + sqr(C.sc - A.sc);
        int z = sqr(C.fs - B.fs) + sqr(C.sc - B.sc);
        int S = abs(Cross({B.fs - A.fs, B.sc - A.sc}, {C.fs - A.fs, C.sc - A.sc}));
        if (x >= y + z) return sqrt(y);
        if (y >= x + z) return sqrt(x);
        return 1.0 * S / sqrt(z);
    }
    
    bool checkOverlap(int radius, int x_center, int y_center, int x1, int y1, int x2, int y2) {
        if (x1 <= x_center && x_center <= x2 && y1 <= y_center && y_center <= y2)
            return true;
        Point a[5];
        a[1] = {x1, y1};
        a[2] = {x2, y1};
        a[3] = {x2, y2};
        a[4] = {x1, y2};
        a[0] = a[4];
        LD minDist = 1e9;
        for (int i = 0; i < 4; i++) {
            minDist = min(minDist, Dist({x_center, y_center}, a[i], a[i + 1]));
        }
        return minDist <= radius;
    }
};