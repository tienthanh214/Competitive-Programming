#include <bits/stdc++.h>

using namespace std;

int n, m, a, b; 

void start(int x) { 
    cout << (x - 1) % m << " " << (x - 1) / m << " "; 
}

void end(int x) { 
    cout << (x - 1) % m + 1 << " " << (x - 1) / m + 1 << " "; 
}

void sol(int a, int b) { 
    int x1 = (a - 1) / m + 1, 
        y1 = (a - 1) % m + 1;
    int x2 = (b - 1) / m + 1, 
        y2 = (b - 1) % m + 1; 
    if (a == 1 && b == n) { 
        cout << 1 << endl; 
        // cout << 0 << " " << 0 << " " << m << " " << m << endl; 
        cout << 0 << " " << 0 << " "; 
        b = ((b - 1) / m + 1) * m;
        end(b); cout << endl; 
        return; 
    }
    if (x1 == x2) { 
        cout << 1 << endl; 
        start(a); end(b); cout << endl; 
        return; 
    }
    if ((y1 == 1 && (y2 == m || b == n))) { 
        cout << 1 << endl; 
        start(a); 
        b = ((b - 1) / m + 1) * m; end(b); cout << endl; 
        return; 
    } 
    if (x1 == x2 - 1) { 
        cout << 2 << endl;
        int nextA = ((a - 1) / m + 1) * m, 
            prevB = (b - 1) / m * m + 1; 
        start(a); end(nextA); cout << endl; 
        start(prevB); end(b); cout << endl; 
        return; 
    }
    if (y1 == 1 && y2 < m) { 
        cout << 2 << endl; 
        int nextA = ((a - 1) / m + 1) * m, 
            prevB = (b - 1) / m * m + 1; 
        start(a); end(prevB - 1); cout << endl; 
        start(prevB); end(b); cout << endl; 
        return; 
    }
    if (y1 > 1 && y2 == m) { 
        cout << 2 << endl; 
        int nextA = ((a - 1) / m + 1) * m, 
            prevB = (b - 1) / m * m + 1; 
        start(a); end(nextA); cout << endl; 
        start(nextA + 1); end(b); cout << endl; 
        return; 
    }
    if (y1 == y2 + 1) { 
        cout << 2 << endl; 
        int nextA = ((a - 1) / m + 1) * m, 
            prevB = (b - 1) / m * m + 1; 
        start(a); end(prevB - 1); cout << endl; 
        start(nextA + 1); end(b); cout << endl; 
        return; 
    }
    if (b == n) { 
        cout << 2 << endl; 
        int nextA = ((a - 1) / m + 1) * m, 
            prevB = (b - 1) / m * m + 1; 
        start(a); end(nextA); cout << endl; 
        start(nextA + 1); 
        b = ((b - 1) / m + 1) * m;
        end(b); cout << endl; 
        return; 
    } 
    {
        cout << 3 << endl; 
        int nextA = ((a - 1) / m + 1) * m, 
            prevB = (b - 1) / m * m + 1; 
        start(a); end(nextA); cout << endl; 
        start(nextA + 1); end(prevB - 1); cout << endl; 
        start(prevB); end(b); cout << endl; 
    }
}

int main() { 
    cin >> n >> m >> a >> b; 
    sol(a, b); 
    // for (int i =1 ; i <= n; ++i) 
    //     for (int j = i; j <= n; ++j) { 
    //         cout << "sol: " << i << " " << j << endl; 
    //         sol(i, j); 
    //         cout << endl; 
    //     }
    

    return 0; 
}