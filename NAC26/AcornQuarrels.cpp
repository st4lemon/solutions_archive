//
#include <bits/stdc++.h>
using namespace std;

vector<int> adj[100005];
int dep[100005];
int ans[100005];

int low[2];

int nc(int i, int c) {
    int low = 0;
    int high = adj[i].size();
    while(low < high) {
        int m = (low + high)/2;
        if(adj[i][m] >= c) {
            high = m;
        }
        else {
            low = m + 1;
        }
    }
//    cout << "nc " << i << " " << c << " " << low << endl;
    return low;
}

void dfs(int n, int par, int p) {
    int v = p;
    if(par != -1) {
        v -= nc(par, n);
        if(par < n) {
            v += adj[par].size();
        }
    }
    low[dep[n]%2] = min(low[dep[n]%2], ans[n]);
//    cout << n << " " << dep[n] << " " << par << " " << v << endl;

    for(int& x : adj[n]) {
        if(x == par) continue;
        dep[x] = dep[n] + 1;
        ans[x] = v + nc(x, n);
        if(x < n) {
            ans[x] -= adj[x].size();
        }
        dfs(x, n, ans[n]);
    }
}

int main() {

    cin.tie(0)->sync_with_stdio(0);

    int N;
    cin >> N;

    for(int i = 0; i<N-1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    

    for(int i = 0; i<N; i++) {
        sort(adj[i].begin(), adj[i].end());
    }

    low[0] = low[1] = 2*N;

    dfs(0, -1, 0);

    for(int i = 0; i<N; i++) {
        ans[i] += N - low[dep[i]%2];
        cout << ans[i] << " \n"[i == N-1];
    }




}
