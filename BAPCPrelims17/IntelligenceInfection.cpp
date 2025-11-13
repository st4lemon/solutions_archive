#include <bits/stdc++.h>

using namespace std;

#define sz(x) (int)x.size()
#define rep(i,a,b) for (int i = a; i < (b); i++)
vector<vector<int>> adj;
vector<vector<int>> g;
int cc = 0;

typedef vector<int> vi;
vi val, comp, z, cont;
int Time, ncomps;

template<class G> int dfs (int j, G& g)
{
    int low = val[j] = ++Time, x; z.push_back(j);
    for (auto e : g[j]) if (comp[e] < 0)
        low = min(low, val[e] ?: dfs(e,g));
    
    if (low == val[j])
    {
        do {
            x = z.back(); z.pop_back();
            comp[x] = ncomps;
            cont.push_back(x);
        } while (x != j);
        
        cont.clear();
        ncomps++;
    }
    return val[j] = low;
}

template<class G> void scc (G &g) {
    int n = sz(g);
    val.assign(n,0);
    comp.assign(n,-1);
    Time = ncomps = 0;
    rep(i,0,n) if (comp[i] < 0) dfs(i,g);
}


int main()
{
    int n, e, c;
    cin >> n >> e >> c;
    adj = vector<vector<int>> (n);
    for (int i = 0; i < c; i++)
    {
        int l, r;
        cin >> l >> r;
        adj[l].push_back(r);
    }
    
    vector<int> b(e);
    for (int i = 0; i < e; i++)
    {
        cin >> b[i];
    }
    
    scc(adj);
    vector<int> bv(ncomps); //#bad in component
    vector<int> tv(ncomps);
    for (int i = 0; i < n; i++)
    {
        tv[comp[i]]++;
    }
    for (int i = 0; i < e; i++)
    {
        bv[comp[b[i]]]++;
    }
    g = vector<vector<int>> (ncomps);
    for (int i = 0; i < n; i++)
    {
        for (auto x : adj[i])
        {
            if (comp[x] != comp[i])
            {
                g[comp[x]].push_back(comp[i]);
            }
        }
    }
    for (int i = 0; i < ncomps; i++)
    {
        sort(g[i].begin(), g[i].end());
        g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end());
    }
    vector<int> in(ncomps);
    
    for (int i = 0; i < ncomps; i++)
    {
        for (auto x : g[i])
        {
            in[x]++;
        }
    }
    
    queue<int> q;
    vector<bool> vis(ncomps);
    for (int i = 0; i < ncomps; i++)
    {
        if (in[i] == 0)
        {
            q.push(i);
        }
    }
    vector<int> sb(ncomps); //have we seen something bad?
    while (!q.empty()) 
    {
        int u = q.front();
        q.pop();
        if (vis[u])
        {
            continue;
        }

        vis[u] = 1;
        if (bv[u] > 0) sb[u] = 1;
        for (auto x : g[u])
        {
            in[x]--;
            sb[x] |= sb[u];
            if (in[x] == 0)
            {
                q.push(x);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < ncomps; i++)
    {
        if (sb[i])
        {
            ans += tv[i] - bv[i];
        } else
        {
            bool ok = 1;
            for (auto x : g[i])
            {
                if (!sb[x])
                {
                    ok = 0;
                }
            }
            ans += ok;
        }
    }

    cout << ans << "\n";
}
