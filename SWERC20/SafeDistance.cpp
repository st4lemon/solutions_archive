#include <bits/stdc++.h>
using namespace std;

typedef pair<double, double> pt;

double X, Y;
int N;

istream& operator>>(istream& is, pt& p) {
    is >> p.first >> p.second;
    return is;
}

pt pts[1005];
vector<pair<int, double>> adj[1005];

double dist(pt& one, pt& two) {
    double d1 = one.first - two.first;
    double d2 = one.second - two.second;
    return d1*d1 + d2*d2;
}

int main() {

    cin >> X >> Y;
    cin >> N;

    double best = 1e18;
    pt start = {0, 0};

    for(int i = 0; i<N; i++) cin >> pts[i];

    for(int i = 0; i<N; i++) {
        for(int j = 0; j<i; j++) {
            // draw edges
            double d = dist(pts[i], pts[j])/4;
            adj[i].emplace_back(j, d);
            adj[j].emplace_back(i, d);
        }
        // draw edges to segments
        double d1 = min(pts[i].first, Y-pts[i].second);
        d1 *= d1;
        adj[N].emplace_back(i, d1);
        adj[i].emplace_back(N, d1);
        double d2 = min(X-pts[i].first, pts[i].second);
        d2 *= d2;
        adj[N+1].emplace_back(i, d2);
        adj[i].emplace_back(N+1, d2);

        best = min(best, dist(start, pts[i]));
    }

    // for(int i = 0; i<N+2; i++) {
    //     cout << i << " | ";
    //     for(auto& [x, d] : adj[i]) {
    //         cout << "(" << x << " " << d << ") ";
    //     }
    //     cout << endl;
    // }

    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> q;
    q.push(make_pair(0.0, N));
    vector<double> dist(N+2, 1e18);
    vector<bool> vis(N+2, false);
    vis[N] = true;
    dist[N] = 0;
    double ans = 0;
    while(!q.empty()) {
        auto [d, x] = q.top();
        q.pop();
        vis[x] = true;
        ans = max(d, ans);
        // cout << x << " : " << d << endl;
        if(x == N+1) break;

        for(auto& [a, b] : adj[x]) {
            if(vis[a]) continue;
            if(dist[a] > b) {
                dist[a] = b;
                q.push(make_pair(b, a));
            }
        }
    }
    // cout << ans << " " << best << endl;
    ans = min(best, ans);
    cout << sqrt(ans) << endl;

}