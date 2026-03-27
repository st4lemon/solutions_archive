//
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll N, L;
ll W, D;
ll f[300005];
vector<ll> loc;
unordered_map<ll, ll> rvi;

bool check(ll T) {
    // cout << "checking " << T << endl;

    vector<int> par(L, 0);
    iota(par.begin(), par.end(), 0);
    vector<int> siz(L, 1);

    auto p = [&](auto&& self, int x) -> int {
        if (par[x] != x) par[x] = self(self, par[x]);
        return par[x];
    };

    auto j = [&](int a, int b) -> void {
        int pa = p(p, a);
        int pb = p(p, b);
        if (pa == pb) return;
        if (siz[pa] < siz[pb]) swap(pa, pb);
        par[pb] = pa;
        siz[pa] += siz[pb];
    };

    vector<ll> pref(2*L, 0);
    vector<ll> pref2(2*L, 0);
    vector<ll> in(L, 0);
    vector<ll> out(L, 0);

    ll times = T / L;
    ll phas = T % L;
    out[0] = times+1;
    out[phas] --;

    // cout << times << " " << phas << " " << T % L << endl;

    for (int i = 1; i<L; i++) {
        out[i] += out[i-1];
    }

    for (int i = 0; i<L; i++) {
        in[i] = out[(i+L-1)%L];
    }

    for (int i = 0; i<N; i++) {
        int l = rvi[f[i]];
        int r = rvi[(f[i]+W)%D];
        if (r <= l) r += L;
        // cout <<i << ": " << l << " " << r << endl;
        pref[l+1]--;
        pref[r]++;
        // cout << "a" << endl;
        if (l+1 < L) {
            pref[l+1+L]--;
            if (r < L) pref[r+L]++;
        }
        pref2[l]--;
        pref2[r]++;
        // cout << "b" << endl;
        if (l < L) {
            pref2[l+L]--;
            if (r < L) pref2[r+L]++;
        }
        j(l%L, r%L);
        // cout << "add interval " << l << " " << r << endl;
    }

    int v = 0;
    int v2 = 0;
    for (int i =0; i<L; i++) {
        v += pref[i];
        if (v > 0) v = 0;
        v2 += pref2[i];
        if (v2 > 0) v2 = 0;
    }

    for (int i = 0; i<L; i++) {
        v += pref[i+L];
        pref[i] = v;
        v2 += pref2[i+L];
        pref2[i] = v2;
    }

    int one = -1, two = -1;
    for (int i = 0; i<L; i++) {
        in[i] += pref[i];
        out[i] += pref[i];
        // cout << in[i] << " - " << out[i] << " " << pref[i] << " " << pref2[i] <<  endl;
        if (pref2[i] + times + (i < phas) < 0) return false;
        if (pref2[i] + times + (i < phas) > 0) j(i, (i+1)%L);
    }

    for (int i = 0; i<L; i++) {
        if (out[i] == in[i] + 1 && i == 0) {
            two = i;
        }
        else if (in[i] == out[i] + 1) {
            if (one >= 0) {
                return false;
            }
            one = i;
        }
        else if (in[i] != out[i]) {
            return false;
        }
    }

    for (int i = 1; i<L; i++) {
        if (p(p, i) != p(p, 0)) return false;
    }

    if (T % L == 0) {
        return (one == -1) && (two == -1);
    }
    return (one >= 0) && (two >= 0);
}

int main() {

    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> W >> D;

    ll ans = 0;

    if (W > D) {
        ans += (N-1) * (W / D) * D;
        W %= D;
        if (W == 0) {
            ans -= (N-1) * D;
            W += D;
        }
    }

    set<ll> locs;
    for (int i = 0; i<N; i++) {
        cin >> f[i];
        locs.insert(f[i]);
        locs.insert((f[i] + W) % D);
    }
    locs.insert(0);

    L = locs.size();
    loc = vector<ll>(locs.begin(), locs.end());

    for (int i = 0; i<L; i++) {
        // cout << i << ": " << loc[i];
        // cout <<  " " << j << " " << loc[j] << endl;
        rvi[loc[i]] = i;
    }

    ll low = 0, high = 2*N*L;
    while (low < high) {
        ll m = (low + high) / 2;
        if (check(m)) {
            high = m;
        }
        else {
            low = m + 1;
        }
    }
    // cout << (low/L)*D + loc[low%L] + ans << endl;
    cout << (low/L)*D + loc[low%L] + ans - W << '\n';



}