#include <bits/stdc++.h>
using namespace std;

int main() {
	
	int N;
	cin >> N;
	
	vector<array<int, 4>> events;
	for(int i = 0; i<N; i++) {
		int x, d;
		cin >> x >> d;
		events.push_back({x-d, 0, x+d, i}); // left, start, right
		events.push_back({x+d, 1, x-d, i});
	}
	
	sort(events.begin(), events.end());
	
	multiset<pair<int, int>> active;
	int ans = 0;
	
	for(auto& [a, k, b, i] : events) {
		// cout << a << " " << k << " " << b << " " << active.size() << endl;
		if(k == 1) {
			if(active.find({a, i}) == active.end()) {
				continue;
			}
			active.erase(active.find({a, i}));
			if(active.empty()) ans++;
			else {
				active.erase(active.begin());
			}
		}
		else {
			active.insert({b, i});
		}
	}
	
	cout << ans << endl;
	
}

