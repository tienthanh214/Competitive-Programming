#include <bits/stdc++.h>

using namespace std;

const int MAXN = (int) 1e5 + 5;

char S[MAXN], T[2 * MAXN];
int n;
int P[2 * MAXN];
int ans = 1;

void Init()
{
     int j = 1;

            T[1] = '#';
            for (int i = 1; i <= n; i++)
               T[++j] = S[i], T[++j] = '#';
            n = j;
            T[0] = '?'; T[n + 1] = '^';
}

void Manacher()
{
     int C = 1; // center
     int R = 1; // center right

            P[1] = 0;
            for (int i = 2; i < n; i++) // current right
            {
                 int j = 2 * C - i; // current left
                 if (i < R) P[i] = min(P[j], R - i);
                    else P[i] = 0;

                 while (T[i - P[i] - 1] == T[i + P[i] + 1]) P[i]++;

                 if (i + P[i] > R)
                 {
                      C = i;
                      R = i + P[i];
                 }
                 ans = max(ans, P[i]);
            }
            printf("%d", ans);
}

int main()
{
            scanf("%d\n", &n);
            scanf("%s", S + 1);
            n = strlen(S + 1);
            Init();
            Manacher();
    return 0;
}
