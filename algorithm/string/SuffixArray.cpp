#include <bits/stdc++.h>

using namespace std;

const int MAXN = (int) 1e5;

char st[MAXN];
int lcp[MAXN], ra[MAXN], idx[MAXN], tmp[MAXN];
int n, K;

void init()
{
         memset(ra, 0, sizeof(ra));
         memset(idx, 0, sizeof(idx));
         memset(lcp, 0, sizeof(lcp));
}

bool cmp(int x, int y)
{
         return (ra[x] < ra[y]) || (ra[x] == ra[y] && ra[x+K] < ra[y+K]);
}

void buildSA() 
{
         for (int i = 1; i <= n; i++) idx[i] = i, ra[i] = st[i];

         for (K = 1; K <= n; K<<=1)
         {
              sort(idx + 1, idx + 1 + n, cmp);
              for (int i = 1; i <= n; i++)
                  tmp[idx[i]] = tmp[idx[i-1]] + cmp(idx[i-1], idx[i]);
              for (int i = 1; i <= n; i++)
                  ra[i] = tmp[i];
              if (ra[idx[n]] == n) break;
         }
}

void LCP() //longest common prefix
{
         for (int i = 1; i <= n; i++) ra[idx[i]] = i;
         lcp[0] = lcp[1] = 0;
         int q = 0;
         for (int i = 1; i <= n; i++)
         {
               int j = idx[ra[i] - 1];
               while (st[i + q] == st[j + q]) q++;
               lcp[ra[i]] = q;
               q--;
               if (q < 0) q = 0;
         }
         //for (int i = 1; i <= n; i++) cout <<lcp[i]<<" ";
         long long ans = 0;
         for (int i = 1; i <= n; i++) ans += (n - idx[i] + 1 - lcp[i]);
         cout << ans << endl; //number of substring set of st
}

int main()
{
            
        scanf("%s", st + 1);
        n = strlen(st + 1);
        init();
        buildSA();
        LCP();
            

    return 0;
}
