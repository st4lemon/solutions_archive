#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll a[100005] = {0};

void printans(vector<array<ll, 3>>& ans) {
	sort(ans.begin(), ans.end());
	cout << ans.size() << endl;
	for(auto& [x, y, z] : ans) {
		cout << x << " " << y << " " << z << endl;
	}
}

int main() {
	
	cin.tie(0)->sync_with_stdio(0);
	
	freopen("magic.in", "r", stdin);
	freopen("magic.out", "w", stdout);
	
	int N;
	cin >> N;
	
	set<pair<ll, ll>> vals;
	
	ll total = 0;
	for(int i = 1; i<=N; i++) {
		cin >> a[i];
		total += a[i];
		vals.emplace(a[i], i);
	}
	
	vector<array<ll, 3>> ans; // push answers into here
	
	// cout << "inputted" << endl;
	
	auto [largest, x] = *vals.rbegin();
	// cout << largest << " " << x << endl;
	if(2*largest >= total) {
		for(ll i = 1; i<=N; i++) {
			if(i == x) continue;
			ll amt = min(a[i], a[x]);
			if(amt == 0) continue;
			ans.push_back({min(i, x), max(i, x), amt});
			a[i] -= amt;
			a[x] -= amt;
			if(a[x] == 0) break;
		}
		
		printans(ans);
		return 0;
	}
	
	//~ if(total % 2 != 0) {
		//~ vals.erase({a[N], N});
		//~ a[N]--;
		//~ vals.emplace(a[N], N);
		//~ total--;
	//~ }
	
	int first = 0;
	int second = 0;
	
	while (total > 0) {
		// cout << first << " " << second << " | " << a[first] << " " << a[second] << endl;
		if(!vals.empty() && total <= 2 * vals.rbegin()->first) {
			// cout << "case 1" << endl;
			// go crazy
			ll x = vals.rbegin()->second;
			for(ll i = first; i<=N; i++) {
				if(i == x) continue;
				if(a[i] == 0) continue;
				ll amt = min(a[i], a[x]);
				if(amt == 0) continue;
				ans.push_back({min(i, x), max(i, x), amt});
				a[i] -= amt;
				a[x] -= amt;
			}
			break;
		}
		else if(a[second] == 0 || second <= first) {
			// cout << "case 1" << endl;
			second++;
			if(second > N) break;
			vals.erase({a[second], second});
		}
		else if(a[first] == 0) {
			// cout << "case 1" << endl;
			first++;
			if(first > N) break;
		}
		else {
			// cout << "case 1" << endl;
			ll cnt = min(a[first], a[second]);
			if(!vals.empty()) cnt = min(cnt, (total + 1) / 2 - vals.rbegin()->first);
			ans.push_back({first, second, cnt});
			a[first] -= cnt;
			a[second] -= cnt;
			total -= 2*cnt;
		}
	}
	
	// cout << "exited" << endl;
	
	printans(ans);
	
}
