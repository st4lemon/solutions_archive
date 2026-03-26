//
#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000005

typedef long long ll;

struct LiChao {
    struct Line {
        ll a, b;
        ll get(ll x) { return a*x + b; }
    };
    ll n;
    static const ll INF = 1e18;
    vector<Line> t;
    vector<pair<ll, ll>> v;
    LiChao(ll _n) : n(_n), t(2*n, {0, -INF}), v(2*n) { build(); }
    void build() {
        for(ll i = 0; i<n; i++) v[i+n] = {i, i+1};
        for(ll i = n-1; i>0; i--) v[i] = {v[2*i].first, v[2*i+1].second};
    }
    void add(ll a, ll b, ll L, ll R) {
        Line l{a, b};
        for(L += n, R += n; L < R; L/=2, R/=2) {
//            cout << "adding line " << a << "x + " << b << " to " << L << " " << R << endl;
            if (L%2) add(l, L++);
            if (R%2) add(l, --R);
        }
    }
    void add(Line l, ll i) {
        if(i >= 2*n) return;
//        cout << "add " << l.a << "x + " << l.b << " to node " << i << endl;
        auto [lo, hi] = v[i];
        ll m = (lo+hi) / 2;
        if(t[i].get(m) < l.get(m)) swap(l, t[i]);
        if(t[i].a < l.a) {
            add(l, 2*i+1);
        } else {
            add(l, 2*i);
        }
    }
    ll q(ll x) {
        ll ans = -INF;
        for (ll i = x+n; i; i/=2) {
//            cout << "getting " << i << endl;
            ans = max(ans, t[i].get(x));
        }
        return ans;
    }
};

ll w[MAXN], h[MAXN];

int main() {

    int N;
    cin >> N;
    int ind = -1;
    ll maxw = 0;
    for(int i = 0; i<N; i++) {
        cin >> h[i] >> w[i];
        if(w[i] > maxw) {
            ind = i;
            maxw = w[i];
        }
    }

//    cout << "rotate by " << ind << endl;

    rotate(w, w+ind, w+N);
    rotate(h, h+ind, h+N);

    ll ans = 0;

    for(int rep = 2; rep--; ) {
        LiChao wt(MAXN), ht(MAXN);
        wt.add(w[0], 0, 0, MAXN);
        ht.add(h[0], 0, 0, MAXN);
        vector<ll> dp(N+1, 0);
        for(int i = 1; i<=N; i++) {
//            cout << i << ": " << h[i-1] << " " << wt.q(h[i-1]) << " " << w[i-1] << " " << ht.q(w[i-1]) << endl;
            dp[i] = max(w[i-1]*h[i-1], max(wt.q(h[i-1]), ht.q(w[i-1])));
            if(i < N) {
                wt.add(w[i], dp[i], 0, MAXN);
                ht.add(h[i], dp[i], 0, MAXN);
            }
            ans = max(ans, dp[i]);
        }

        rotate(w, w+1, w+N);
        rotate(h, h+1, h+N);
    }

    cout << ans << endl;





}
