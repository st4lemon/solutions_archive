//
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vl;

struct Seg {
    int n;
    vl arr, mn, sm, lazy;
    // maintains (min, sum of arr[i] where tree[i] == min)
    Seg(vl& a) : n((int)a.size()), arr(a), mn(2*n, 0), sm(2*n, 0), lazy(2*n, 0) { build(0, 0, n); }

    void build(int N, int L, int R) {
        int M = (L+R)/2;
        if (R-L == 1) {
            mn[N] = 0;
            sm[N] = arr[L];
            return;
        }
        build(N+1, L, M);
        build(N+2*(M-L), M, R);
        sm[N] = sm[N+1] + sm[N+2*(M-L)];
    }

    ll query() {
        if (lazy[0] != 0) {
            int M = n/2;
            mn[0] += lazy[0];
            if (n > 1) {
                lazy[1] += lazy[0];
                lazy[2*M] += lazy[0];
            }
            lazy[0] = 0;
        }
        if (mn[0] == 0) {
            return sm[0];
        }
        return 0;
    }

    void upd(int N, int L, int R, int x, int y, int val) {
        int M = (L+R)/2;
        if (lazy[N] != 0) {
            mn[N] += lazy[N];
            if (R-L > 1) {
                lazy[N+1] += lazy[N];
                lazy[N+2*(M-L)] += lazy[N];
            }
            lazy[N] = 0;
        }
        if (y <= L || R <= x || R <= L) return;
        if (x <= L && R <= y) {
            mn[N] += val;
            if (R-L > 1) {
                lazy[N+1] += val;
                lazy[N+2*(M-L)] += val;
            }
            return; // sm doesn't change
        }
        upd(N+1, L, M, x, y, val);
        upd(N+2*(M-L), M, R, x, y, val);
        mn[N] = min(mn[N+1], mn[N+2*(M-L)]);
        sm[N] = 0;
        if (mn[N] == mn[N+1]) sm[N] += sm[N+1];
        if (mn[N] == mn[N+2*(M-L)]) sm[N] += sm[N+2*(M-L)];
    }

};

struct RMQ {
    vector<vector<int>> jmp;
    RMQ(const vector<int>& V) : jmp(1, V) {
        for (int pw = 1, k = 1; pw * 2 <= (int)V.size(); pw *= 2, ++k) {
            jmp.emplace_back((int)V.size() + 1 - pw * 2);
            for (int j = 0; j<jmp[k].size(); j++) {
                jmp[k][j] = min(jmp[k-1][j], jmp[k-1][j+pw]);
            }
        }
    }
    int query(int a, int b) {
        int dep = 31 - __builtin_clz(b-a);
        return min(jmp[dep][a], jmp[dep][b-(1<<dep)]);
    }
};

struct LCA {
    int T = 0;
    vector<int> time, path, ret;
    RMQ rmq;

    LCA(vector<vector<pair<ll, ll>>> &C) : time(C.size()), rmq((dfs(C, C.size()-1, -1), ret)) {}

    void dfs(vector<vector<pair<ll, ll>>>& C, int v, int par) {
        time[v] = T++;
        for (auto [y, d] : C[v]) if (y != par) {
            path.push_back(v), ret.push_back(time[v]);
            dfs(C, y, v);
        }
    }

    int lca(int a, int b) {
        if (a==b) return a;
        tie(a, b) = minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }
};

int main() {

    cin.tie(0)->sync_with_stdio(0);

    int N, K;
    cin >> N >> K;

    vector<vector<pair<ll, ll>>> adj(N);
    vector<int> in(N, 0);
    for (int i = 0; i<N; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        in[a]++;
        in[b]++;

        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }

    vector<bool> cycle(N, true);

    // cout << "one" << endl;

    // iteratively remove nodes with indegree = 1 to identify cycle nodes
    queue<int> q;
    for (int i = 0; i<N; i++) if (in[i] == 1) q.push(i);

    while (!q.empty()) {
        int n = q.front();
        q.pop();
        cycle[n] = false;
        for (auto& [x, d]: adj[n]) {
            in[x]--;
            if (in[x] == 1) q.push(x);
        }
    }

    // cout << "two" << endl;

    // dfs to construct a tree to perform
    vector<int> par(N, -1);
    vector<int> grp(N, -1);
    vector<vector<pair<ll, ll>>> adj2(N);
    auto dfs = [&](auto&& self, int n, int p, int g) -> void {
        par[n] = p;
        grp[n] = g;
        for (auto& [x, d] : adj[n]) {
            if (x == p) continue;
            if (cycle[x]) continue;
            adj2[n].emplace_back(x, d);
            self(self, x, n, g);
        }
    };

    adj2.emplace_back();
    for (int i = 0; i<N; i++) {
        if (cycle[i]) {
            dfs(dfs, i, N, i); // gets all parents
            adj2[N].emplace_back(i, 0);
        }
    }

    // cout << "three" << endl;
    LCA l(adj2);

    // cout << "four" << endl;

    vector<int> active(N, 0);


    vector<pair<int, int>> iv;
    for (int i = 0; i<K; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        int x = l.lca(a, b);
        if (x == N) {
            active[grp[a]]--;
            active[grp[b]]--;
            iv.emplace_back(grp[a], grp[b]);
        }
        else {
            active[x]-=2;
        }
        active[a]++;
        active[b]++;
    }

    // cout << "five" << endl;
    ll tot = 0;
    auto dfs2 = [&](auto&& self, int n, int p) -> int {
        int v = active[n];
        for (auto& [x, d] : adj[n]) {
            if (x == p) continue;
            if (cycle[x]) continue;
            int k = self(self, x, n);
            if (k > 0) tot += d;
            v += k;
        }
        return v;
    };

    for (int i = 0; i<N; i++) {
        if (cycle[i]) {
            dfs2(dfs2, i, N);
        }
    }

    // now to make the cycle work
    vector<int> cyc;
    vector<int> rev(N, -1);
    vector<ll> val;
    int p = 0;
    for (; p<N; p++) {
        if (cycle[p]) break;
    }

    // cout << "six" << endl;
    while (cycle[p]) {
        rev[p] = cyc.size();
        cyc.push_back(p);
        cycle[p] = false;
        for (auto& [x, d] : adj[p]) {
            if (cycle[x]) {
                p = x;
                val.push_back(d);
                break;
            }
        }
        if (val.size() != cyc.size()) {
            for (auto& [x, d] : adj[p]) {
                if (x == cyc[0]) {
                    val.push_back(d);
                    break;
                }
            }
        }
    }

    // cout << "seven" << endl;

    // cout << val.size() << " " << cyc.size() << endl;
    assert(val.size() == cyc.size());

    vector<array<int, 3>> evs;
    int V = val.size();

    ll sum = 0;
    for (int i = 0; i<V; i++) {
        // cout << cyc[i] << " " << val[i] << endl;
        sum += val[i];
    }


    Seg s(val);
    for (int i = 0; i<iv.size(); i++) {
        auto& [x, y] = iv[i];
        int rx = rev[x];
        int ry = rev[y];
        if (rx > ry) {
            swap(rx, ry);
        }
        x = rx;
        y = ry;
        evs.push_back({x, i, -1});
        evs.push_back({y, i, 1});
        s.upd(0, 0, V, x, y, 1);
        // cout << "updating " << x << " " << y << endl;
    }

    sort(evs.begin(), evs.end());
    ll best = s.query();

    // cout << "best " << best << endl;

    int e = 0;
    for (int i = 0; i<V; i++) {
        while (e < evs.size() && evs[e][0] <= i) {
            // apply event
            s.upd(0, 0, V, iv[evs[e][1]].first, iv[evs[e][1]].second, evs[e][2]);
            s.upd(0, 0, V, 0, iv[evs[e][1]].first, -evs[e][2]);
            s.upd(0, 0, V, iv[evs[e][1]].second, V, -evs[e][2]);
            e++;
        }
        best = max(best, s.query());
    }

    tot += sum - best;
    cout << tot << endl;

}
