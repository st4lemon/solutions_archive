#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef complex<double> C;
#define fi first
#define se second
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rep(i,a,b) for (int i = a; i < (b); i++)
const int MOD = 258280327;
#define MAXK 131073

struct Combo
{
    vl in = {1}, f = {1};
    ll binpow (ll a, ll b = MOD - 2)
    {
        ll res = 1;
        while (b > 0)
        {
            if (b % 2)
            {
                res = res * a % MOD;
            }
            a = a * a % MOD;
            b /= 2;
        }
        return res;
    }
    ll fact (ll x)
    {
        if (x < 0) return 0;
        while (sz(f) <= x)
        {
            f.push_back(sz(f) * f.back() % MOD);
        }
        return f[x];
    }
    ll inv (ll x)
    {
        if (x < 0) return 0;
        while (sz(in) <= x)
        {
            in.push_back(binpow(sz(in)) * in.back() % MOD);
        }
        return in[x];
    }

    ll choose (ll n, ll k)
    {
        if (n < k || k < 0) return 0;
        return fact(n) * inv(k) % MOD * inv(n-k) % MOD;
    }
} c;    

typedef vector<double> vd;
void fft(vector<C>& a) {
    int n = sz(a), L = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1);
    static vector<C> rt(2, 1);
    for (static int k = 2; k < n; k *= 2) {
        R.resize(n); rt.resize(n);
        auto x = polar(1.0L, acos(-1.0L) / k);
        rep(i, k, 2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
    }
    vi rev(n);
    rep(i, 0, n) rev[i] = (rev[i/2] | (i & 1) << L) / 2;
    rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2) 
        for (int i = 0; i<n; i += 2*k) rep(j, 0, k) {
            C z = rt[j+k] * a[i+j+k];
            a[i+j+k] = a[i+j] - z;
            a[i+j] += z;
        }
}

vl convMod(const vl &a, const vl &b) {
    if (a.empty() || b.empty()) return {};
    vl res(sz(a) + sz(b) - 1);
    int B = 32-__builtin_clz(sz(res)), n=1<<B, cut=int(sqrt(MOD));
    vector<C> L(n), R(n), outs(n), outl(n);
    rep(i, 0, sz(a)) L[i] = C((int)a[i] / cut, (int) a[i] % cut);
    rep(i, 0, sz(b)) R[i] = C((int)b[i] / cut, (int) b[i] % cut);
    fft(L), fft(R);
    rep(i, 0, n) {
        int j = -i & (n-1);
        outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
        outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
    }
    fft(outl), fft(outs);
    rep(i, 0, sz(res)) {
        ll av = ll(real(outl[i])+.5), cv = ll(imag(outs[i])+.5);
        ll bv = ll(imag(outl[i])+.5) + ll(real(outs[i])+.5);
        res[i] = ((av % MOD * cut + bv) % MOD * cut + cv) % MOD;
    }
    if(sz(res)>MAXK) res.resize(MAXK);
    return res;
}

vl conv(const vl& _a, const vl& _b) {
    vd a(sz(_a)), b(sz(_b));
    rep(i, 0, sz(_a)) a[i] = (double)_a[i];
    rep(i, 0, sz(_b)) b[i] = (double)_b[i];

    if(a.empty() || b.empty()) return {};
    vd res(sz(a) + sz(b) - 1);
    int L = 32 - __builtin_clz(sz(res)), n = 1<<L;
    vector<C> in(n), out(n);
    copy(all(a), begin(in));
    rep(i,0,sz(b)) in[i].imag(b[i]);
    fft(in);
    for (C& x : in) x *= x;
    rep(i, 0, n) out[i] = in[-i & (n-1)] - conj(in[i]);
    fft(out);
    rep(i,0,sz(res)) res[i] = imag(out[i]) / (4*n);
    
    vl ret(sz(res));
    rep(i,0,sz(res)) {
        ret[i] = ll(res[i] + .5) % MOD;
    }
    if(sz(ret)>MAXK) ret.resize(MAXK);

    return ret;

}

vl add(const vl& a, const vl& b) {
    vl res(max(sz(a), sz(b)));
    rep(i, 0, max(sz(a), sz(b))) {
        if(i < sz(a)) res[i] += a[i];
        if(i < sz(b)) res[i] += b[i];
        res[i] %= MOD;
    }
    return res;
}

void shift(vl& v) {
    v.push_back(v.back());
    for(int i = sz(v)-1; i>0; i--) {
        v[i] = v[i-1];
    }
    v[0] = 0;
}

int main() {
    
    freopen("dichromatic.in", "r", stdin);
    freopen("dichromatic.out", "w", stdout);
    
    int K, H;
    cin >> K >> H;

    vector<vector<vl>> dp(H+1, vector<vl>(2));
    dp[0][0] = vl(2,0);
    dp[0][1] = vl(2,1);

    for(int h = 1; h<=H; h++) {
        vl t = add(dp[h-1][0], dp[h-1][1]);
        dp[h][0] = convMod(t, t);
        shift(dp[h][0]);
        dp[h][1] = convMod(dp[h][0], dp[h][0]);
        shift(dp[h][1]);
    }

    // for(int h = 0; h<=H; h++) {
    //     cout << h << " " << 0 << " | ";
    //     for(int i = 0; i<min(sz(dp[h][0]), 32); i++) {
    //         cout << dp[h][0][i] << " ";
    //     }
    //     cout << endl;
    //     cout << h << " " << 1 << " | ";
    //     for(int i = 0; i<min(sz(dp[h][1]), 32); i++) {
    //         cout << dp[h][1][i] << " ";
    //     }
    //     cout << endl;
    // }

    vl ans(MAXK, 0);
    for(int k = 0; k<MAXK; k++) {
        for(int h = 0; h<=H; h++) {
            if(sz(dp[h][0]) > k) ans[k] += dp[h][0][k];
            if(sz(dp[h][1]) > k) ans[k] += dp[h][1][k];
            ans[k] %= MOD;
        }
    }

    for(int i = 0; i<K; i++) {
        int a;
        cin >> a;
        cout << ans[a] << " \n"[i == K-1];
    }

    

}
