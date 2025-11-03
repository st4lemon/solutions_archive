//
// Created by David on 10/12/2025.
//
#include <bits/stdc++.h>
using namespace std;

#define MAXK 19

typedef long long ll;

ll H[200005] = {0};
int lft[200005] = {0};
int rht[200005] = {0};
int lbl[MAXK][200005] = {{0}}; // stores index
int rbl[MAXK][200005] = {{0}}; // stores index
ll lsum[MAXK][200005] = {{0}}; // stores sum
ll rsum[MAXK][200005] = {{0}}; // stores sum

int main() {

    int N;
    cin >> N;

    for(int i = 0; i<N-1; i++) cin >> H[i];

    vector<int> stk;
    stk.push_back(-1);
    for(int i = 0; i<N-1; i++) {
        while(stk.back() >= 0 && H[stk.back()] <= H[i]) {
            stk.pop_back();
        }
        lft[i] = stk.back();
        stk.push_back(i);
    }

    stk = vector<int>(1, N-1);
    for(int i = N-2; i>=0; i--) {
        while(stk.back() < N-1 && H[stk.back()] <= H[i]) {
            stk.pop_back();
        }
        rht[i] = stk.back();
        stk.push_back(i);
    }

    for(int i = 0; i<N-1; i++) {
        lbl[0][i] = lft[i];
        rbl[0][i] = rht[i];
        lsum[0][i] = (i - lft[i]) * H[i];
        rsum[0][i] = (rht[i] - i) * H[i];
        // cout << lbl[0][i] << " " << lsum[0][i] << " | " << rbl[0][i] << " " << rsum[0][i] << endl;
    }

    for(int k = 1; k<MAXK; k++) {
        // cout << endl;
        for(int i = 0; i<N-1; i++) {
            if(lbl[k-1][i] == -1) {
                lbl[k][i] = lbl[k-1][i];
                lsum[k][i] = lsum[k-1][i];
            }
            else {
                lbl[k][i] = lbl[k-1][lbl[k-1][i]];
                lsum[k][i] = lsum[k-1][i] + lsum[k-1][lbl[k-1][i]];
            }

            if(rbl[k-1][i] == N-1) {
                rbl[k][i] = rbl[k-1][i];
                rsum[k][i] = rsum[k-1][i];
            }
            else {
                rbl[k][i] = rbl[k - 1][rbl[k - 1][i]];
                rsum[k][i] = rsum[k - 1][i] + rsum[k - 1][rbl[k - 1][i]];
            }

            // cout << lbl[k][i] << " " << lsum[k][i] << " | " << rbl[k][i] << " " << rsum[k][i] << endl;
        }
    }

    int Q;
    cin >> Q;
    while(Q--) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        // cout << a << " " << b << endl;
        if(a < b) {
            // use left
            b--;
            ll ans = 0;
            for(int k = MAXK-1; k>=0; k--) {
                if(lbl[k][b] >= a) {
                    ans += lsum[k][b];
                    b = lbl[k][b];
                }
            }
            cout << ans + lsum[0][b] << endl;
        }
        else {
            // use right
            a--;
            ll ans = 0;
            for(int k = MAXK-1; k>=0; k--) {
                if(rbl[k][b] <= a) {
                    ans += rsum[k][b];
                    b = rbl[k][b];
                }
            }
            cout << ans + rsum[0][b] << endl;
        }

    }

}

