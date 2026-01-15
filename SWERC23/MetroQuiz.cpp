//
#include <bits/stdc++.h>
using namespace std;

#define MAXN 1LL<<18

typedef long long ll;

ll N, M;
ll station[18] = {0};

unordered_map<ll, ll> dp;

ll dfs(ll mask) {
	if(dp.count(mask)) return dp[mask];
	int cnt = __builtin_popcountll(mask);
	ll best = 50*50;
	for(int m = 0; m<N; m++) {
		ll num = station[m] & mask;
		if(num == 0 || num == mask) continue;
		best = min(best, dfs(num) + dfs(mask - num));
	}
	dp[mask] = best+cnt;
	// cout << bitset<5>(mask) << ": " << best + cnt << '\n';
	return best + cnt;
}


int main() {
	
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> N >> M;
	
	for(int i = 0; i<M; i++) {
		int k;
		cin >> k;
		for(int j = 0; j<k; j++) {
			int l;
			cin >> l;
			station[l] |= 1LL<<i;
		}
	}
	
	for(ll i = 1; i< 1LL<<M; i *= 2) {
		dp[i] = 0;
	}
		
	double ans = dfs((1LL<<M) - 1);
	if(ans >= 50*50) {
		cout << "not possible" << '\n';
		return 0;
	}
	cout << fixed << setprecision(8) << ans/M << '\n';
	
}
