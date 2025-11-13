#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define MOD 1'000'000'007

ll dp[2][305][305] = {{{0}}};

// dp[1][h][w] = height is h, weight is w
// dp[0][h][w] = height is <h, weight is wj
// dp[1][h] = knapsack using dp[1][h-1] and dp[0][h-1] minus knapsack using dp[0-][h-1]
// dp[0][h] = dp[0][h-1] + dp[1][h-1]

int main() {
    
    int H, W;
    cin >> H >> W;
    
    dp[1][0][0] = 1;
    for(int k = 1; k<=H; k++) {
        // cout << k << endl;
        // compute two knapsacks
        vector<ll> knap(W+1, 0);
        knap[0] = 1;
        for(int i = 0; i<W; i++) {
            for(int j = 0; i+j+1<=W; j++) {
                knap[i+j+1] += knap[i] * ( (dp[1][k-1][j] + dp[0][k-1][j]) % MOD );
                knap[i+j+1] %= MOD;
            }
        }
        vector<ll> sub(W+1, 0);
        sub[0] = 1;
        for(int i = 0; i<W; i++) {
            for(int j = 0; i+j+1 <= W; j++) {
                sub[i+j+1] += sub[i] * dp[0][k-1][j];
                sub[i+j+1] %= MOD;
            }
        }
        //~ for(int i = 0; i<=W; i++) {
            //~ cout << knap[i] << " ";
        //~ }
        //~ cout << endl;
        //~ for(int i = 0; i<=W; i++) {
            //~ cout << sub[i] << " ";
        //~ }
        //~ cout << endl;
            
        for(int i = 0; i<=W; i++) {
            dp[1][k][i] = (knap[i] - sub[i] + MOD) % MOD;
        }
        for(int i = 0; i<=W; i++) {
            dp[0][k][i] = (dp[0][k-1][i] + dp[1][k-1][i]) % MOD;
        }
    }
    
    //~ for(int i = 0; i<=H; i++) {
        //~ for(int j = 0; j<=W; j++) {
            //~ cout << dp[1][i][j] << " ";
        //~ }
        //~ cout << endl;
    //~ }
    //~ cout << endl;
    
    
    //~ for(int i = 0; i<=H; i++) {
        //~ for(int j = 0; j<=W; j++) {
            //~ cout << dp[0][i][j] << " ";
        //~ }
        //~ cout << endl;
    //~ }
    //~ cout << endl;
    
    cout << dp[1][H-1][W-1] << endl;
    
    
}
