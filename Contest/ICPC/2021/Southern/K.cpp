#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10; 

int n; 
long long y, z; 
long long a[N]; 

int main() {    
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n; 
    for (int i = 1; i <= n; ++i) 
        cin >> a[i]; 
    cin >> y >> z; 

    long long assDist = z - y; 
    if (assDist < 0) 
        assDist = -assDist; 
    multiset<long long> st; 
    for (int i = 1; i <= n; ++i) { 
        long long tdist = a[i] - z; 
        if (tdist < 0) 
            tdist = -tdist; 
        st.insert(tdist); 
    }
    
    int res = 0; 
    while (st.size() && assDist > 0) { 
        long long cur = *st.begin(); 
        st.erase(st.begin()); 
        if (cur >= assDist) 
            break; 
        assDist -= cur; 
        res++; 
    }
    
    cout << res << endl; 

    return 0; 
}