#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 10; 
const int Mod = 1e9 + 7;
const int LOG = 21; 

long long n, fPow[10][N];

int f(int x) { 
    int ret = 1; 
    while (x > 0) { 
        ret *= (x % 10); 
        x /= 10; 
    }
    return ret; 
}



string L, R;

long long res = 1;

struct Number{
    long long cnt[10];

    Number(){
        for (int i = 0; i < 10; i++) cnt[i] = 0;
    }

    void makeZero(){
        for (int i = 0; i < 10; i++) cnt[i] = 0;
    }

    void Mul(int x){
        if (x == 0){
            //makeZero();
            return;
        }
        for (int i = 2; i <= 7; i++) {
            while (x % i == 0){
                x /= i;
                cnt[i]++;
            }
        }
    }

    void MulPow(int x, int p){
        if (x == 0){
            //makeZero();
            return;
        }
        for (int i = 2; i <= 7; i++) {
            while (x % i == 0){
                x /= i;
                cnt[i] += p;
            }
        }
    }

    bool isok(Number other){
        Number ret;
        ret.makeZero();
        for (int i = 2; i <= 7; i++) ret.cnt[i] = other.cnt[i] - cnt[i];
        long double tmp = 0;
        for (int i = 2; i <= 7; i++){
            tmp += log(i) * ret.cnt[i];
        }
        return tmp >= 0;
    }

    long long Calculate(){
        long long ret = 1;
        for (int i = 2; i <= 7; i++) if (cnt[i] > 0){
            ret = ret * fPow[i][cnt[i]] % Mod;
        }
        return ret; 
    }

    void print(){
        for (int i = 2; i <= 7; i++) if (cnt[i] > 0) cout << i << ": " << cnt[i] << endl;
        cout << endl;
    }
};

void Solve(string L, string R){
    Number best, cur;
    best.makeZero();
    cur.makeZero();
    //cout << L << " " << R << " " << n << endl;
    bool isequal = true;
    for (int i = 0; i < n; i++){
        int x = R[i] - '0';
        int y = L[i] - '0';
        if (x == y && isequal){
            //res = res * x % Mod;
            if (x != 0) cur.Mul(x);
            else{
                cout << 0 << endl;
                return;
            }
            continue;;
        }
        isequal = false;
        Number tmp = cur;
        cur.Mul(x);
        if (x == 1 && i > 0) continue;;
        tmp.Mul(x - 1);
        //cout << "Ye " << tmp.Calculate() << endl;
        tmp.MulPow(9, n - i - 1);
       // cout << "Ye " << tmp.Calculate() << endl;
      //  tmp.print();
        if (best.isok(tmp)) best = tmp;
      //  cout << cur.Calculate() << " " << tmp.Calculate() << " " << best.Calculate() << endl;
    }
    if (best.isok(cur)) best = cur;
    cout << best.Calculate() << endl;
    //cout << "end\n";
}

int main() { 
    int l, r;
    cin >> L >> R;
    // L = to_string(l);
    // R = to_string(r);
    n = R.size();
    reverse(L.begin(), L.end());
    while (L.size() < R.size()){
        L.push_back('0');
    } 
    reverse(L.begin(), L.end());

    for (int x = 1; x <= 9; x++) {
        fPow[x][0] = 1;
        for (int i = 1; i <= 3 * n; i++) fPow[x][i] = fPow[x][i - 1] * x % Mod;
    }
    

    Solve(L, R);
    // int ret = f(l), tmp = l; 
    // for (int i = l; i <= r; ++i) {
    //    if (ret < f(i)){
    //         ret = f(i);
    //         tmp = i;
    //    }
    //    //cout << i << " " << ret << " " << tmp << endl;
    // }
    // cout << ret << endl; 
    // cout << tmp << endl;
    return 0; 
}