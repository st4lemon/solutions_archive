#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ld long double
#define x first
#define y second
using pt = pair<int,int>;
const ld PI = acos(-1);

ld md(ld A) {
	A += 6*PI;
	while (A >= 2*PI) A -= 2*PI;
	return A;
}

ld ang(pt a, pt b) {
	ld A = atan2(b.y-a.y,b.x-a.x);
	return md(A);
}

signed main() {
	cin.tie(0)->sync_with_stdio(0);
	
	freopen("ambitious.in","r",stdin);
	freopen("ambitious.out","w",stdout);

	while (1) {
		int n,m,k;
		cin >> n;
		if (n == 0) return 0;
		vector<pt> d(n);
		for (auto &p : d) cin >> p.x >> p.y;
		cin >> m;
		vector<pt> f(m);
		for (auto &p : f) cin >> p.x >> p.y;
		cin >> k;
		vector<pt> t(k);
		for (auto &p : t) cin >> p.x >> p.y;
		int ans = 0;
		for (auto c : f) {
			vector<pair<ld,bool>> td;
			for (auto p : t) {
				ld A = ang(c,p);
				td.push_back({A,0});
			}
			for (auto p : d) {
				ld A = ang(c,p);
				td.push_back({A,1});
			}
			queue<pair<ld,bool>> cur;
			sort(td.begin(),td.end());
			int ct = 0, cd = 0, cdt = 0;
			for (auto [A,D] : td) {
				if (A < PI) continue;
				ct++;
				cur.push({A-2*PI,D});
			}
			for (auto [A,D] : td) {
				while (cur.size() && A - cur.front().x >= PI) {
					auto [AB,DB] = cur.front();
					if (DB) {
						cd--;
					} else {
						cdt -= cd;
						ct--;
					}
					cur.pop();
				}
				if (D) {
					cdt += ct;
					cd++;
				} else {
					ans += cdt;
					ct++;
				}
				cur.push({A,D});
				//~ queue<pair<ld,bool>> Q = cur;
				//~ while (Q.size()) {
					//~ cout << Q.front().x << ' ' << Q.front().y << '\n';
					//~ Q.pop();
				//~ }
				//~ cout << "ct,cd,cdt: " << ct << ' ' << cd << ' ' << cdt << '\n';
				//~ cout << "ans: " << ans << '\n';
				//~ cout << '\n';
			}
		}
		cout << ans << '\n';
	}
}
