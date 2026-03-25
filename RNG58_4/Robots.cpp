#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int N;
ll T;
ll x[100005], y[100005];
int d[100005], ind[100005];
bool act[100005];
ll vis[100005][4];
vector<array<pair<ll, ll>, 4>> adj;


map<char, int> mp = {
    {'U', 0},
    {'R', 1},
    {'D', 2},
    {'L', 3}
};

ll dx[4] = {0, 1, 0, -1};
ll dy[4] = {1, 0, -1, 0};

int main() {

    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> T;

    for(int i = 0; i<N; i++) {
        char c;
        cin >> x[i] >> y[i] >> c;
        d[i] = mp[c];
        act[i] = false;
        fill(vis[i], vis[i]+4, 2*T);
    }

    iota(ind, ind+N, 0);
    sort(ind, ind+N, [&](auto& a, auto& b){
        return tie(x[a], y[a], a) < tie(x[b], y[b], b);
    });

    adj.resize(N);
    for(int i = 1; i<N; i++) {
        if(x[ind[i-1]] == x[ind[i]]) {
            adj[ind[i-1]][0] = {ind[i], abs(y[ind[i-1]] - y[ind[i]])};
            adj[ind[i]][2] = {ind[i-1], abs(y[ind[i-1]] - y[ind[i]])};
        }
    }

    sort(ind, ind+N, [&](auto& a, auto& b){
        return tie(y[a], x[a], a) < tie(y[b], x[b], b);
    });
    for(int i = 1; i<N; i++) {
        if(y[ind[i-1]] == y[ind[i]]) {
            adj[ind[i-1]][1] = {ind[i], abs(x[ind[i-1]] - x[ind[i]])};
            adj[ind[i]][3] = {ind[i-1], abs(x[ind[i-1]] - x[ind[i]])};
        }
    }

    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<>> q;
    act[0] = true;
    vis[0][d[0]] = 0;
    q.push({0, 0, d[0]});

    while(!q.empty()) {
        auto [t, x, dir] = q.top();
        q.pop(); // assume vis has been done already

        if(!act[x]) { // if not activated
            act[x] = true;
            if(dir != d[x]) { // if moving in different direction than activator
                if(adj[x][d[x]].second > 0 && vis[adj[x][d[x]].first][d[x]] > t + adj[x][d[x]].second) { // check if next move exists/isbetter
                    vis[adj[x][d[x]].first][d[x]] = t + adj[x][d[x]].second;
                    q.push({t+adj[x][d[x]].second, adj[x][d[x]].first, d[x]}); // take that move.
                }
            }
        }
        if(adj[x][dir].second > 0 && vis[adj[x][dir].first][dir] > t + adj[x][dir].second) { // continue moving current robot
            vis[adj[x][dir].first][dir] = t + adj[x][dir].second;
            q.push({t + adj[x][dir].second, adj[x][dir].first, dir}); // continue traveling in that direction
        }

    }

    for(int i = 0; i<N; i++) {
        ll a = min(T, min(min(vis[i][0], vis[i][1]), min(vis[i][2], vis[i][3])));
        a = T - a;
        cout << x[i] + dx[d[i]] * a << " " << y[i] + dy[d[i]] * a << '\n';
    }

}