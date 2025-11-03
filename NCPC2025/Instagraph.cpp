#include <bits/stdc++.h>
using namespace std;

int N, M;
set<int> fans[200005];

int main() {
	
	cin >> N >> M;
	for(int i = 0; i<M; i++) {
		int a, b;
		cin >> a >> b;
		if(fans[a].count(b) == 0) {
			fans[b].insert(a);
		}
		else {
			fans[a].erase(b);
		}
	}
	
	int ans = 1;
	int best = fans[1].size();
	for(int i = 2; i<=N; i++) {
		if((int)(fans[i].size()) > best) {
			ans = i;
			best = (int)(fans[i].size());
		} 
	}
	
	cout << ans << " " << best << endl;
	
}
