#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

int N, H, W;
pii books[105];
int tw = 0;

struct comp {
	bool operator()(const int& one, const int& two) {
		return books[one].first > books[two].first;
	}
};

vector<bool> knap(int lim) {
	// lim: books taller than lim go upright
	// gap: horizontal gap for vertical books
	// H: height of shelf
	int gap = W - lim;
	
	if(gap + H < tw) {
		// cout << "gap " << lim << endl;
		return {};
	}
	
	vector<vector<bool>> k(N+1, vector<bool>(H+1, false));
	vector<vector<int>> back(N+1, vector<int>(H+1, -1));
	k[0][0] = true;
	
	for(int i = 1; i<=N; i++) {
		for(int j = H; j>=0; j--) {
			if(books[i-1].first <= H) { // try placing book vertically
				if(k[i-1][j]) { 
					k[i][j] = true;
					back[i][j] = j;
					continue;
				}
			}
			if(books[i-1].first > lim) {
				continue;
			}
			if(j >= books[i-1].second) { // try placing book horizontally (after we try it). 
				if(k[i-1][j-books[i-1].second]) {
					k[i][j] = true;
					back[i][j] = j-books[i-1].second;
					continue;
				}
			}
		}
	}
	
	int best = 0;
	for(int i = 0; i<=H; i++) {
		if(k[N][i]) best = i;
	}
	
	if(tw - best + lim > W) {
		// cout << "wide " << lim << endl;
		return {};
	}
	
	
	int cnt = 0;
	vector<bool> stacked(N, false);
	for(int i = N; i>0; i--) {
		// cout << i << " " << best << endl;
		if(back[i][best] == -1) {
			// cout << "tootall " << lim << endl;
			return {};
		}
		if(back[i][best] != best) {
			stacked[i-1] = true;
			best = back[i][best];
			cnt ++;
		}
	}
	if(cnt == N) {
		int i = 0;
		while(i < N && books[i].first > H) {
			i++;
		}
		if(i == N) return {}; // there is nothing under height H
		for(int j = i+1; j<N; j++) {
			if(books[j].first > H) continue;
			if(books[j].second < books[i].second) {
				i = j;
			}
		}
		if(books[i].second + lim > W) return {};
		stacked[i] = false;
		return stacked;
	}
	// cout << lim << " " << gap << endl;
	
	return stacked;
}

int main() {
	
	cin >> N >> H >> W;
	
	for(int i = 0; i<N; i++) {
		cin >> books[i].first >> books[i].second;
		tw += books[i].second;
	}
	
	for(int i = 0; i<N; i++) {
		if(books[i].first > W) continue;
		vector<bool> poss = knap(books[i].first);
		if(poss.empty()) continue;
		vector<int> upright;
		for(int j = 0; j<N; j++) {
			if(!poss[j]) upright.push_back(j);
		}
		
		vector<int> stacked;
		for(int j = 0; j<N; j++) {
			if(poss[j]) stacked.push_back(j);
		}
		sort(stacked.begin(), stacked.end(), comp());
		
		cout << "upright";
		for(int& k : upright) {
			cout << " " << k+1;
		}
		cout << endl;
		cout << "stacked";
		for(int& k : stacked) {
			cout << " " << k+1;
		}
		cout << endl;
		
		
		return 0;
	}
	
	cout << "impossible" << endl;
	
	
	
}