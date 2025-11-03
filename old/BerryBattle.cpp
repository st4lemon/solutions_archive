// NCPC 2022 #B: Berry Battle
// https://codeforces.com/gym/104030/problem/B 
#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // find diameter
    vector<int> dist1(n + 1, -1);
    auto dfs1 = [&](auto&& self, int node, int par = 0) -> void {
        dist1[node] = dist1[par] + 1;
        for (int nei : adj[node]) if (nei != par) self(self, nei, node);
    };

    dfs1(dfs1, 1);

    vector<int> dist2(n + 1, -1), par2(n + 1, 0);
    auto dfs2 = [&](auto&& self, int node, int par = 0) -> void {
        dist2[node] = dist2[par] + 1;
        par2[node] = par;
        for (int nei : adj[node]) if (nei != par) self(self, nei, node);
    };

    int endpt = 1;
    for (int i = 2; i <= n; i++) {
        if (dist1[i] > dist1[endpt]) endpt = i;
    }

    dfs2(dfs2, endpt);

    int second_endpt = endpt;
    for (int i = 1; i <= n; i++) if (dist2[i] > dist2[second_endpt]) second_endpt = i;

    vector<int> diameter;
    vector<int> marked(n + 1, 0);
    while (second_endpt != 0) {
        diameter.push_back(second_endpt);
        second_endpt = par2[second_endpt];
    }

    // for (int val : diameter) cout << val << " ";
    // cout << endl;

    if (diameter.size() <= 3) {
        cout << "NO\n";
        return 0;
    }

    // center, then outside
    int cnt;
    queue<int> q;
    if (diameter.size() <= 5) {
        marked[diameter[2]] = 1;
        marked[diameter[3]] = 2;
        q.push(diameter[2]);
        q.push(diameter[3]);
        cnt = 3;
    } else if (diameter.size() % 2 == 0) {
        cnt = 1;
        for (int i = diameter.size() - 3; i >= diameter.size() / 2 - 1; i--) {
            marked[diameter[i]] = cnt++;
            q.push(diameter[i]);
        }
    } else { // odd case
        marked[diameter[0]] = 1;
        cnt = 2;
        for (int i = diameter.size() - 4; i >= diameter.size() / 2 - 1; i--) {
            marked[diameter[i]] = cnt++;
            q.push(diameter[i]);
        }
    }

    while (!q.empty()) {
        int node = q.front(); q.pop();
        for (int nei : adj[node]) {
            if (marked[nei] > 0) continue;
            marked[nei] = cnt++;
            q.push(nei);
        }
    }

    // for (int i = 1; i <= n; i++) cout << marked[i] << " ";
    // cout << endl;
 
    vector<int> ans(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        ans[marked[i]] = i;
    }

    bool works = true;
    for (int i = 1; i <= n; i++) if (ans[i] == 0) works = false;

    if (!works) cout << "NO\n";
    else {
        cout << "YES\n";
        for (int i = 1; i <= n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    



    return 0;
}
