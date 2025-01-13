// Codeforces Round 972 #E1: Subtangle Game (easy)
// https://codeforces.com/contest/2005/problem/E1
#include <bits/stdc++.h>
using namespace std;

int grid[305][305] = {{0}};
int dp[305][305][305] = {{{0}}};

void solve() {

    int L, N, M;
    cin >> L >> N >> M;
    vector<int> A;
    for(int i = 0; i<L; i++) {
        int a;
        cin >> a;
        A.push_back(a);
    }

    for(int i = 0; i<N; i++) {
        for(int j = 0; j<M; j++) {
            cin >> grid[i][j];
        }
    }

    for(int i = 0; i<=N; i++) {
        for(int j = 0; j<=M; j++) {
            for(int k = 0; k<=L; k++) {
                if(i == N || j == M || k == L) {
                    dp[i][j][k] = -2; // universally losing state
                }
                else dp[i][j][k] = 0;
            }
        }
    }

    vector<int> moves(N, -1); // moves[i]: opponent has no moves if curr j > moves[i]
    vector<int> wins(N, -1); // wins[i]: opponent has no winning state if curr j > wins[i]

    for(int k = L-1; k>=0; k--) { // process moves in reverse order
        int win = k%2 == 0 ? 1 : -1; // p1 is 1, p2 is -1
        for(int i = N-1; i>=0; i--) {
            for(int j = M-1; j>=0; j--) {
                // check if winning state exists
                if(grid[i][j] != A[k]) continue;
                if(j >= moves[i] || j >= wins[i]) {
                    dp[i][j][k] = win;
                }
                else {
                    dp[i][j][k] = -win;
                }
            }
        }
        // precompute moves and wins
        int pw = 0;
        int pm = 0;
        for(int i = N-1; i>=0; i--) {
            wins[i] = pw;
            moves[i] = pm;
            // pw = 0;
            // pm = 0;
            for(int j = 0; j < M; j++) {
                if(dp[i][j][k] == win) {
                    pw = max(pw,  j);
                }
                if(grid[i][j] == A[k]) {
                    pm = max(pm, j);
                }
            }
            if(i < N-1) {
                pw = max(pw, wins[i+1]);
                pm = max(pm, moves[i+1]);
            }
        }
/*
        for(int i = 0; i<N; i++) {
            for(int j = 0; j<M; j++) {
                cout << dp[i][j][k] << " ";
            }
            cout << endl;
        }

        for(int i = 0; i<N; i++) {
            cout << wins[i] << " ";
        }
        cout << endl;
        for(int j = 0; j<N; j++) {
            cout << moves[j] << " ";
        }
        cout << endl << endl;
*/
    }

    for(int i = 0; i<N; i++) {
        for(int j = 0; j<M; j++) {
            if(dp[i][j][0] == 1) {
                cout << "T" << endl;
                return;
            }
        }
    }

    cout << "N" << endl;

}

int main() {

    int T;
    cin >> T;
    for(int i = 0; i<T; i++) {
        solve();
    }

}
/*
1
3 7 7
1 2 2
1 4 4 4 4 4 4
4 4 4 4 4 2 4
4 4 4 4 4 4 4
4 4 4 4 2 4 4
4 4 4 2 4 4 4
4 2 4 4 4 4 4
4 4 4 4 4 4 4
 */
