#include <bits/stdc++.h>
using namespace std;

bool dp1[5001][5001];
bool dp2[5001][5001];

int main() {

    string s, t;
    cin >> s >> t;

    int N = s.length();
    int M = t.length();

    dp2[N][M] = true;

    for(int i = N; i>=0; i--) {
        for(int j = M-1; j>=i; j--) {
            if(i == N) {
                dp2[i][j] = true;
            }
            else {
                // if s[i] = t[j+1], then we cannot match s[i] to t[j]. this only works if s[i+1] can be matched to t[j+1] already. 
                dp1[i][j] = ((j < M-1 && s[i] == t[j+1]) ? dp1[i+1][j+1] : dp2[i+1][j+1]) && s[i] == t[j]; 
                // either we can match here, or we matched previously already. 
                dp2[i][j] = dp1[i][j] || dp2[i][j+1];
            }
        }
    }
// if s[i] = t[j+1], then we cannot match 
    // for(int i = 0; i<=N; i++) {
    //     for(int j = 0; j<=M; j++) {
    //         cout << (dp1[i][j] ? 1 : 0);
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    // for(int i = 0; i<=N; i++) {
    //     for(int j = 0; j<=M; j++) {
    //         cout << (dp2[i][j] ? 1 : 0);
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    if(dp1[0][0]) {
        cout << "Yes" << endl;
    }
    else cout << "No" << endl;

}