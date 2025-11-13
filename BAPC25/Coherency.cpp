#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ld long double
#define f first
#define s second

ld LEN = 50.8+80+80;
const int INF = 1e9;

struct DSU {
	int n;
	vector<int> par, sz;
	int cmp;
	DSU(int _n) : n(_n), par(n), sz(n,1), cmp(n) {
		for (int i = 0; i < n; i++) par[i] = i;
	}
	int r(int x) { return x == par[x] ? x : (par[x] = r(par[x])); }
	void u(int x, int y) {
		int rx = r(x), ry = r(y);
		if (rx == ry) return;
		if (sz[rx] < sz[ry]) swap(rx, ry);
		sz[rx] += sz[ry];
		par[ry] = rx;
		cmp--;
	}
};

bool conn(vector<array<int,3>> &cs, int x, int y) {
	ld d = ((ld)cs[x][0]-(ld)cs[y][0])*((ld)cs[x][0]-(ld)cs[y][0]) + ((ld)cs[x][1]-(ld)cs[y][1])*((ld)cs[x][1]-(ld)cs[y][1]);
	return sqrt(d) <= (ld)cs[x][2]/2+(ld)cs[y][2]/2+50.8;
}

signed main() {
	cin.tie(0)->sync_with_stdio(0);
	
	int n;
	cin >> n;
	vector<array<int,3>> cs(n);
	for (auto &x : cs) {
		for (auto &y : x) cin >> y;
	}
	sort(cs.begin(),cs.end());
	set<array<int,3>> cur; // sorted by y
	DSU D(n);
	vector<int> deg(n,0);
	for (int l = 0, r = 0; r < n; r++) {
		while (cs[l][0] < cs[r][0]-LEN) {
			cur.erase({cs[l][1], cs[l][0], l});
			l++;
		}
		auto L = cur.lower_bound({(int)(cs[r][1]-LEN),-INF,-INF});
		auto R = cur.upper_bound({(int)(1+cs[r][1]+LEN),INF,INF});
		while (L != R) {
			if (conn(cs, (*L)[2], r)) D.u((*L)[2], r), deg[(*L)[2]]++, deg[r]++;
			L++;
		}
		cur.insert({cs[r][1], cs[r][0], r});
	}
	if (n < 7) {
		cout << (D.cmp == 1 ? "yes\n" : "no\n");
	} else {
		cout << (D.cmp == 1 && *min_element(deg.begin(),deg.end()) >= 2 ? "yes\n" : "no\n");
	}
}
