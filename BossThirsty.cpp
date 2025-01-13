// Codeforces Round 977 D: Boss, Thirsty
#include <bits/stdc++.h>

using namespace std;

void print(vector<vector<long long>>& vec) {
    for(int i = 0; i<vec.size(); i++) {
        for(int j = 0; j<vec[i].size(); j++) {
            if(vec[i][j] == -1e18) cout << "- ";
            else cout << vec[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

}

void solve() {

    int N, M;
    cin >> N >> M;

    // idea:
    // make dpL, dpR
    //     dpL[i][k] = best sum possible on the i-th day with left endpoint at k
    // transition:
    //     dpL[i][k] =
    //         over all segments with left endpoint at k, for k < p < r
    //         max(dpL[i-1][p], dpR[i-1][p]) + pref[r] - pref[l-1]
    //         make an auxiliary array to help calc these things:
    //         aux[p] = max(pref[i>=p]) + max(dpL[i-1][p], dpR[i-1][p])
    //         basically, aux[p] picks a segment ending at p and takes the best interval containing an endpoint
    //     dpL[i][k] = max(aux[p>k])

    vector<vector<long long>> dpL(N, vector<long long>(M, -1e18));
    vector<vector<long long>> dpR(N, vector<long long>(M, -1e18));
    vector<vector<long long>> grid(N, vector<long long>(M));

    for(int i = 0; i<N; i++) {
        for(int j = 0; j<M; j++) {
            cin >> grid[i][j];
        }
    }

    vector<long long> prefL(M+1, 0);
    vector<long long> maxL(M+1, 0);
    vector<long long> prefR(M+1, 0);
    vector<long long> maxR(M+1, 0);
    for(int j = 0; j<M; j++) {
        prefR[j+1] = prefR[j] + grid[0][j];
        maxR[j+1] = max(-prefR[j+1], maxR[j]);
        dpR[0][j] = prefR[j+1] + maxR[j];
    }

    for(int j = M-1; j>=0; j--) {
        prefL[j] = prefL[j+1] + grid[0][j];
        maxL[j] = max(-prefL[j], maxL[j+1]);
        dpL[0][j] = prefL[j] + maxL[j+1];
    }

    vector<long long> auxL(M+1, -1e18);
    // auxL[i] = max over all k > i:
    //     for each endpoint k in the previous layer
    //     if right endpoint, cannot intersect with last elem of prefix
    //     if left endpoint, can intersect with last elem of prefix
    // dpL[i][j] = prefL[j] + max(auxL[j+1], dpR[i-1][j] + maxL[j+1])
    vector<long long> auxR(M+1, -1e18);
    for(int i = 1; i<N; i++) {
        for(int j = 0; j<M; j++) {
            // calculate prefix up to j
            prefR[j+1] = prefR[j] + grid[i][j];
            // find largest -prefix in suffix starting at j
            maxR[j+1] = max(-prefR[j+1], maxR[j]);
            // calculate aux
            auxR[j+1] = max(auxR[j], dpR[i-1][j] + maxR[j]);
            if(j > 0) {
                auxR[j+1] = max(auxR[j+1], dpL[i-1][j] + maxR[j-1]);
                dpR[i][j] = prefR[j+1] + max(auxR[j], dpL[i-1][j] + maxR[j-1]);
            }
        }


        for(int j = M-1; j>=0; j--) {
            // calculate prefix up to j
            prefL[j] = prefL[j+1] + grid[i][j];
            // find largest -prefix in suffix starting at j
            maxL[j] = max(-prefL[j], maxL[j+1]);
            // calculate aux:
            auxL[j] = max(auxL[j+1], dpL[i-1][j]+ maxL[j+1]);
            if(j < M-1) {
                auxL[j] = max(auxL[j], dpR[i-1][j] + maxL[j+2]);
                dpL[i][j] = prefL[j] + max(auxL[j+1], dpR[i-1][j]+maxL[j+2]);
            }
        }
    }

    long long ans = -1e18;
    for(int i = 0; i<M; i++) {
        ans = max(ans, max(dpL[N-1][i], dpR[N-1][i]));
    }
    cout << ans << endl;

}

int main() {

    int T;
    cin >> T;
    for(int i = 0; i<T; i++) solve();

}
