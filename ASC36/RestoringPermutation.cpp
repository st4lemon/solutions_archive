#include <bits/stdc++.h>
using namespace std;

int main() {
	
	freopen("restore.in", "r", stdin);
	freopen("restore.out", "w", stdout);
	
	int N;
	cin >> N;
	
	vector<int> ans(2*N, -1);
	vector<int> leftover(N);
	for(int i = 1; i<=N; i++) {
		int a;
		cin >> a;
		if(a < i) {
			ans[2*(i-1)] = 2*i-1;
			ans[2*i-1] = -a;
			leftover[i-1] = 2*i;
		}
		else if(a > i) {
			ans[2*i-1] = 2*i;
			ans[2*(i-1)] = -a;
			leftover[i-1] = 2*i-1;
		}
		else {
			cout << -1 << endl;
			return 0;
		}
	}
	
	for(int i = 0; i<N; i++) {
		if(ans[2*i] < 0) {
			int ind = -ans[2*i]-1;
			ans[2*i] = leftover[ind];
		}
		if(ans[2*i+1] < 0) {
			int ind = -ans[2*i+1]-1;
			ans[2*i+1] = leftover[ind];
		}
	}
	
	for(int i = 0; i<2*N; i++) {
		cout << ans[i] << " ";
	}
	cout << endl;
	
}
