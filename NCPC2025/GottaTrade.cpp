#include <bits/stdc++.h>
using namespace std;

int N, M, K;
vector<int> adj[200005];
bool vis[200005] = {0};
vector<vector<int>> comps;
int col[200005] = {0};
	
	
int floodfill(int x, int c) {
	comps.emplace_back(0);
	queue<int> q;
	q.push(x);
	vis[x] = true;
	int ret = 0;
	while(!q.empty()) {
		int n = q.front();
		q.pop();
		comps[c].push_back(n);
		ret++;
		for(int& k : adj[n]) {
			if(vis[k]) continue;
			vis[k] = true;
			q.push(k);
		}
	}
	return ret;
}

int main() {
	
	cin >> N >> M >> K;
	
	for(int i = 0; i<M; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	for(int i = 0; i<N; i++) {
		if(!vis[i]) {
			if(floodfill(i, comps.size()) < K) {
				cout << "impossible" << endl;
				return 0;
			}
		}
	}
	
	for(int i = 0; i<(int)(comps.size()); i++) {
		for(int j = 0; j<(int)(comps[i].size()); j++) {
			col[comps[i][j]] = (j%K) + 1;
		}
	}
	
	for(int i = 0; i<N; i++) {
		cout << col[i] << " ";
	}
	cout << endl;
	
	
}