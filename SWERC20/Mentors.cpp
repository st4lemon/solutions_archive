#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll R, N, M;

ll dp[2023][2023] = {{0}};
// dp[i][j] = at position i, and there are j people that need mentors. count # ways
// dp[0][0] = 1; 
// dp[i][j] = 
//        (person i takes no mentees) dp[i-1][j-1]
//        (person i takes 1 mentee) dp[i-1][j]
//        (person i takes 2 mentees) dp[i-1][j+1]

int main() {

    cin >> R >> N >> M;

    dp[0][0] = 1;
    for(int i = 1; i<=N; i++) {
        // cout << i << endl;
        for(int j = 1; j<=N; j++) {
            if(i == R) { // take no mentees
                dp[i][j] += dp[i-1][j-1]; // 
            }
            else {
                dp[i][j] += dp[i-1][j-1]; // take no mentees
                dp[i][j] += 1LL * j * dp[i-1][j]; // take 1 mentee, j ways to choose
                if(j < N) {
                    dp[i][j] += 1LL * (j+1) * j / 2 * dp[i-1][j+1]; // take 2 mentees, j+1 choose 2 ways to choose
                }
            }
            dp[i][j] %= M;
            // cout << dp[i][j] << " ";
        }
        // cout << endl;
    }
    // cout << endl;


    cout << dp[N][1] << endl;
    

}