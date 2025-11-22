//
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int N;

bool oncyc[300005] = {0};
ll fd[300005] = {0};
ll fdi[300005] = {0};
ll sd[300005] = {0};
ll D[300005] = {0};
vector<pair<ll, ll>> adj[300005];

bool vis[300005] = {0};
vector<pair<ll, ll>> cyc, rcyc;
ll tcyc = 0;

int findcyc(int n, int par) {
    // cout << n << " " << par << endl;
    if(vis[n]) {
        return n;
    }
    vis[n] = true;
    for(auto& [x, d] : adj[n]) {
        if(x == par) continue;
        int res = findcyc(x, n);
        if(res == n) {
            cyc.emplace_back(n, d);
            rcyc.emplace_back(x, d);
            oncyc[n] = true;
            tcyc += d;
            return -2;
        }
        else if(res == -2) {
            return -2;
        }
        else if(res >= 0) {
            cyc.emplace_back(n, d);
            rcyc.emplace_back(x, d);
            oncyc[n] = true;
            tcyc += d;
            return res;
        }
    }
    return -1;
}

void dfs1(int n, int par) {
    for(auto& [x, d] : adj[n]) {
        if(x == par || oncyc[x]) {
            continue;
        }
        dfs1(x, n);
        if(fd[x] + d > fd[n]) {
            sd[n] = fd[n];
            fd[n] = fd[x] + d;
            fdi[n] = x;
        }
        else if(fd[x] + d > sd[n]) {
            sd[n] = fd[x] + d;
        }
    }
}

ll ans[300005] = {0};

void dfs2(int n, int par, ll pd) {
    ans[n] = max(fd[n], pd);
    for(auto& [x, d] : adj[n]) {
        if(x == par || oncyc[x]) {
            continue;
        }
        if(x == fdi[n]) {
            dfs2(x, n, d + max(sd[n], pd));
        }
        else {
            dfs2(x, n, d + max(fd[n], pd));
        }
    }
}

int main() {

    cin >> N;

    for(int i = 0; i<N; i++) {
        ll a, b, d;
        cin >> a >> b >> d;
        a--;
        b--;
        adj[a].emplace_back(b, d);
        adj[b].emplace_back(a, d);
    }

    findcyc(0, -1);
    reverse(rcyc.begin(), rcyc.end());

//    cout << endl;
//    for(auto& [x, d] : cyc) {
//        cout << x << " " << d << endl;
//    }
//    cout << endl;
//    for(auto& [x, d] : rcyc) {
//        cout << x << " " << d << endl;
//    }

    // from each cycle node do the rerooting dp
    fill(fdi, fdi+N, -1);

    for(auto& [x, d] : cyc) {
        dfs1(x, -1);
    }

    int C = cyc.size();
    ll pref = 0;
    ll last = 0;
    int ind = 0;
    multiset<ll> dists;
    for(int i = 0; i<C; i++) {
        // precondition: ind >= i
        while(last + cyc[ind % C].second <= pref + tcyc / 2) {
            last += cyc[ind % C].second;
            dists.insert(last + fd[cyc[ind % C].first]);
            ind += 1;
        }
        if(!dists.empty()) {
            D[cyc[(i+C-1)%C].first] = max(D[cyc[(i+C-1)%C].first], *(dists.rbegin()) - pref);
        }
        // get rid of elem i
        pref += cyc[i].second;
        if(dists.find(pref + fd[cyc[i].first]) != dists.end()) {
            dists.erase(dists.find(pref + fd[cyc[i].first]));
        }
    }

    pref = 0;
    last = 0;
    ind = 0;
    dists.clear();
    for(int i = 0; i<C; i++) {
        // precondition: ind >= i
        while(last + rcyc[ind % C].second <= pref + tcyc / 2) {
            last += rcyc[ind % C].second;
            dists.insert(last + fd[rcyc[ind % C].first]);
            ind += 1;
        }
        if(!dists.empty()) {
            D[rcyc[(i+C-1)%C].first] = max(D[rcyc[(i+C-1)%C].first], *(dists.rbegin()) - pref);
        }
        // get rid of elem i
        pref += rcyc[i].second;
        if(dists.find(pref + fd[rcyc[i].first]) != dists.end()) {
            dists.erase(dists.find(pref + fd[rcyc[i].first]));
        }
    }

    for(auto& [x, d] : cyc) {
        dfs2(x, -1, D[x]);
    }

    for(int i = 0; i<N; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;

//    for(int i = 0; i<N; i++) {
//        cout << D[i] << " ";
//    }
//    cout << endl;
//    for(int i = 0; i<N; i++) {
//        cout << fd[i] << " ";
//    }
//    cout << endl;
//    for(int i = 0; i<N; i++) {
//        cout << sd[i] << " ";
//    }
//    cout << endl;



}
