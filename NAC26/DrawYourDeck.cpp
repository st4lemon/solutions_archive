//
#include <bits/stdc++.h>
using namespace std;

/*
 * stars and bars
 * suppose there are k ones
 * then n-k other things, n-k+1 locations allowing after 0s
 * and then n-k not allowing after 0s.
 *
 * so n choose k versus n-1 choose k.
 *
 */

int cnt[4];

int main() {

    int N, K;
    cin >> N >> K;

    if(N == 1) {
        cout << 1.0 << endl;
        return 0;
    }

    int tot = 0;
    for(int i = 0; i<=K; i++) {
        cin >> cnt[i];
        tot += i * cnt[i];
    }

    if(tot < N-1) {
        cout << 0.0 << endl;
        return 0;
    }

    vector<vector<vector<double>>> dp(cnt[0]+1, vector<vector<double>>(cnt[2]+1, vector<double>(cnt[3]+1, 0)));
    dp[cnt[0]][cnt[2]][cnt[3]] = 1;

    for(int i = cnt[0]; i>=0; i--) {
        for(int j = cnt[2]; j>=0; j--) {
            for(int k = cnt[3]; k>=0; k--) {
                double rem = (i+j+k);
                int val = (cnt[2] - j) + 2*(cnt[3] - k) - (cnt[0] - i); // amt taken so far
                // val must be at least 0.
//                cout << i << " " << j << " " << k << " " << dp[i][j][k] << endl;
                if(val < 0) continue;

                // take 0
                if(i > 0) {
                    dp[i-1][j][k] += i / rem * dp[i][j][k];
                }

                // take 2
                if(j > 0) {
                    dp[i][j-1][k] += j / rem * dp[i][j][k];
                }

                // take 3
                if(k > 0) {
                    dp[i][j][k-1] += k / rem * dp[i][j][k];
                }
            }
        }
    }

    double ans = 0;
    if(tot >= N-1 && cnt[0] > 0) {
//        cout << "0 " <<  dp[1][0][0] << endl;
        ans += dp[1][0][0];
    }
    if(tot - 2 >= N-1 && cnt[2] > 0) {
//        cout << "2 " <<  dp[1][0][0] << endl;
        ans += dp[0][1][0];
    }
    if(tot - 3 >= N-1 && cnt[3] > 0) {
//        cout << "3 " <<  dp[1][0][0] << endl;
        ans += dp[0][0][1];
    }

    if(tot == N-1) {
        ans *= 1.0 * (N-cnt[1]) / N;
    }

    cout << fixed << setprecision(8) << ans << endl;


}

