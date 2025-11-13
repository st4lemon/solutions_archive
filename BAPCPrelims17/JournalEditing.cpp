#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 7;
const int MAXN = 21;
int dp[1 << MAXN];
int c[MAXN][1 << MAXN];

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < (1 << n); j++)
        {
            c[i][j] = INF;
        }
    }
    for (int j = 0; j < (1 << n); j++)
    {
        dp[j] = INF;
    }
    for (int i = 0; i < n; i++)
    {
        int p;
        cin >> p;
        for (int j = 0; j < p; j++)
        {
            //each of the proofs
            int u;
            cin >> u; //cost
            int k;
            cin >> k; //deps
            int v = 0;
            for (int l = 0; l < k; l++)
            {
                int x;
                cin >> x;
                v |= (1 << x);
            }
            //~ cout << "cost: " << i << " " << v << " " << u << "\n";
            c[i][v] = min(c[i][v], u);
        }
    }
    //process costs
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < (1 << n); j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (j & (1 << k))
                {
                    c[i][j] = min(c[i][j], c[i][j^(1<<k)]);
                }
            }
        }
    }
    
    int ans = INF;
    dp[0] = 0;
    for (int i = 0; i < (1 << n); i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j))
            {
                //consider adding j
                dp[i] = min(dp[i], dp[i^(1<<j)] + c[j][i]);
            }
        }
        if (i & 1) ans = min(ans, dp[i]);
    }
    
    cout << ans << "\n";
    
    
    return 0;
}