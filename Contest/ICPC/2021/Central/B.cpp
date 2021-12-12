#include <iostream> 
#include <vector>

using namespace std;

const int MOD = 1e9 + 7; 

int main() { 
    ios_base::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0); 

    int n, type0 = 0, type1 = 0, type2 = 0; 
    cin >> n; 
    vector<int> a(n); 
    // type0: x == 0
    // type1: x < 0 
    // type2: x > 0
    for (int &x: a) {  
        cin >> x; 
        type0 += x == 0; 
        type1 += x < 0; 
        type2 += x > 0; 
    }

    auto getRes = [=, &a] (int value) { 
        int ret = 1; 
        for (int x: a) { 
            if (x == value) { 
                value = -1e9 - 10; 
                continue; 
            }
            ret = 1ll * ret * x % MOD; 
        }
        return ret; 
    };

    int res = 1; 
    if (type0 > 1) { 
        res = 0; 
    } else if (type0 == 1) { 
        if (type1 % 2 == 0) { 
            res = getRes(0);  
        } else { 
            res = 0; 
        }
    } else { 
        if (type1 % 2 == 0) { 
            res = getRes(-1e9 - 10); 
        } else { 
            int maxElement = (int)(-1e9); 
            for (int x: a) 
                if (x < 0) 
                    maxElement = max(maxElement, x); 
            res = getRes(maxElement); 
        }
    }
    
    if (res < 0) 
        res += MOD; 
    cout << res << endl; 

    return 0; 
}