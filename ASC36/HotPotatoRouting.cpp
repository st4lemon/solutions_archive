#include <bits/stdc++.h>
using namespace std;

int L[105] = {0};
int a[105][8] = {{0}};

int s[105];
int stime[105];
int e[105];
int etime[105];

int main() {
	
	freopen("hot.in", "r", stdin);
	freopen("hot.out", "w", stdout);
	
	int N;
	cin >> N;
	
	for(int i = 0; i<N; i++) {
		cin >> L[i];
		for(int j = 0; j<L[i]; j++) {
			cin >> a[i][j];
			a[i][j]--;
		}
	}
	
	int P;
	cin >> P;
	
	for(int i = 0; i<P; i++) {
		cin >> s[i] >> e[i] >> stime[i];
		s[i]--;
		e[i]--;
	}
	
	vector<pair<int, int>> events;
	
	for(int i = 0; i<P; i++) {
		int t = stime[i];
		int x = s[i];
		while(t <= stime[i] + 840*N) {
			x = a[x][t % L[x]];
			t++;
			if(x == e[i]) break;
		}
		if(x == e[i]) {
			etime[i] = t;
			events.emplace_back(stime[i], i);
		}
	}
	
	sort(events.begin(), events.end());
	
	int curr = 0;
	vector<int> loc(N, -1);
	set<int> ans;
	//~ int active = 0;
	for(int i = 0; i<=840*N + 1000; i++) {
		vector<int> next(N, -1);
		while(curr < (int)events.size() && events[curr].first == i) { // put starting packets
			int x = events[curr].second;
			if(loc[s[x]] == -1) {
				loc[s[x]] = x; // if empty, put it in start position
				//~ active++;
			}
			else {
				if(etime[loc[s[x]]] > etime[x] || (etime[loc[s[x]]] == etime[x] && x < loc[s[x]])) { // if not empty, replace if ends sooner
					loc[s[x]] = x;
				}
			}
			curr++;
		}
		//~ if(active > 0) {
			//~ cout << i << ": ";
			//~ for(int k = 0; k<N; k++) {
				//~ cout << loc[k] << " \n"[k == N-1];
			//~ }
			
		//~ }
		for(int j = 0; j<N; j++) { // start from all locs
			if(loc[j] == -1) continue;
			if(j == e[loc[j]]) { // check packets that are ending
				ans.insert(loc[j]);
				//~ active--;
				continue;
			}
			int y = a[j][i % L[j]]; // find next location from node
			if(next[y] == -1) next[y] = loc[j]; // if next location is empty, put packet there
			else {
				if(etime[next[y]] > etime[loc[j]] || (etime[next[y]] == etime[loc[j]] && loc[j] < next[y])) { // if not empty but ends sooner than packet there, set it.
					next[y] = loc[j];
				}
				//~ active--; // collision occurred, less actives for sure. 
			}
		}
		loc = next;
		//~ if(active > 0) {
			//~ for(int k = 0; k<N; k++) {
				//~ cout << next[k] << " \n"[k == N-1];
			//~ }
			
		//~ }
		
	}
	
	cout << ans.size() << endl;
	for(const int& a : ans) {
		cout << a+1 << " ";
	}
	cout << endl;
	
}
