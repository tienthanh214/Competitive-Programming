#include <stdio.h>
#include <string.h>

using namespace std;

typedef long long LL;

const LL base = (LL) 1e9 + 2142001;
const int MAXN = (int) 1e6 + 5;

char T[MAXN], P[MAXN];
LL Pow[MAXN], hashT[MAXN];
int n, m;

LL getHash(int i, int j) {
    return (hashT[j] - hashT[i - 1] * Pow[j - i + 1] + (LL)base * base) % base;
}

void buildHash() {
    Pow[0] = 1;
    for (int i = 1; i <= n; i++)
        Pow[i] = (Pow[i - 1] * 31LL) % base;
    for (int i = 1; i <= n; i++)
        hashT[i] = (hashT[i - 1] * 31LL+ T[i] - 'a') % base;
}

void findSubString() {
     LL hashP = 0;
    for (int i = 1; i <= m; i++)
        hashP = (hashP * 31 + P[i] - 'a') % base;

    for (int i = 1; i <= n - m + 1; i++)
        if (getHash(i, i + m - 1) == hashP) 
            printf("%d ", i);

}

int main() {
    scanf("%s", T + 1); //string
    scanf("%s", P + 1); //patern
    n = strlen(T + 1);
    m = strlen(P + 1);
    buildHash();
    findSubString();

    return 0;
}
