#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXN = (int) 1e6 + 6;

int n, m;
char s[MAXN];
char t[MAXN];
int pi[MAXN];

void KMP() {
    int k = 0;
    pi[1] = 0;
    for (int i = 2; i <= m; i++) {
        while (k > 0 && s[k + 1] != s[i])
            k = pi[k];
        if (s[k + 1] == s[i]) k++;
        pi[i] = k;
    }
}

void findSubstring() {
    int k = 0;
    for (int i = 1; i <= n; i++) {
        while (k > 0 && s[k + 1] != t[i])
            k = pi[k];
        if (s[k + 1] == t[i]) k++;
        if (k == m) {
            printf("%d ", i - m + 1);
            k = pi[k];
        }
    }
}

int main()
{
    scanf("%s", t + 1); //patern
    scanf("%s", s + 1); //string
    n = strlen(t + 1);
    m = strlen(s + 1);
    KMP();
    findSubstring();

    return 0;
}
