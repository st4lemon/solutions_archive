#include <bits/stdc++.h>
using namespace std;

map<char, int> alphabet;
string alphastr;

int s[2001];
int t[2001];

int N, M;

void fillS() {
	string S;
	cin >> S;
	N = S.length();
	for(int i = 0; i<N; i++) {
		s[i] = alphabet[S[i]];
	}
}

void fillT() {
	string S;
	cin >> S;
	M = S.length();
	for(int i = 0; i<M; i++) {
		t[i] = alphabet[S[i]];
	}
}

int dp[2001][2001];
short back[2001][2001] = {{0}};

pair<int, int> ms[201];
pair<int, int> mt[201];

int adj[201][201];

void fillAdj() {
	int K = alphastr.size();
	for(int i = 0; i<K; i++) {
		for(int j = 0; j<K; j++) {
			cin >> adj[i][j];
		}
	}
	
	for(int i = 0; i<K; i++) {
		ms[i] = {adj[i][0], 0};
		for(int j = 1; j<K; j++) {
			ms[i] = min(ms[i], {adj[i][j], j});
		}
	}
		
	for(int j = 0; j<K; j++) {
		mt[j] = {adj[0][j], 0};
		for(int i = 1; i<K; i++) {
			mt[j] = min(mt[j], {adj[i][j], i});
		}
	}
		
}

int main() {
	
	freopen("dissim.in", "r", stdin);
	freopen("dissim.out", "w", stdout);
	
	cin >> alphastr;
	for(int i = 0; i<(int)alphastr.size(); i++) {
		alphabet[alphastr[i]] = i;
	}
	
	fillS();
	fillT();
	fillAdj();
	
	
	for(int i = 0; i<=N; i++) {
		for(int j = 0; j<=M; j++) {
			if(i > 0 || j > 0) dp[i][j] = 1e9;
			if(i > 0) {
				if(dp[i][j] > dp[i-1][j] + ms[s[i-1]].first) {
					dp[i][j] = dp[i-1][j] + ms[s[i-1]].first;
					back[i][j] = 1;
				}
			}
			if(j > 0) {
				if(dp[i][j] > dp[i][j-1] + mt[t[j-1]].first) {
					dp[i][j] = dp[i][j-1] + mt[t[j-1]].first;
					back[i][j] = 2;
				}
			}
			if(i > 0 && j > 0) {
				if(dp[i][j] > dp[i-1][j-1] + adj[s[i-1]][t[j-1]]) {
					dp[i][j] = dp[i-1][j-1] + adj[s[i-1]][t[j-1]];
					back[i][j] = 3;
				}
			}
		}
	}
	
	vector<char> ans;
	vector<char> ant;
	int cs = N, ct = M;
	while(cs > 0 || ct > 0) {
		if(back[cs][ct] == 1) {
			cs--;
			ans.push_back(alphastr[s[cs]]);
			ant.push_back(alphastr[ms[s[cs]].second]);
		}
		else if(back[cs][ct] == 2) {
			ct--;
			ans.push_back(alphastr[mt[t[ct]].second]);
			ant.push_back(alphastr[t[ct]]);
		}
		else {
			cs--;
			ct--;
			ans.push_back(alphastr[s[cs]]);
			ant.push_back(alphastr[t[ct]]);
		}
	}
	
	cout << dp[N][M] << endl;
	for(auto it = ans.rbegin(); it != ans.rend(); it++) {
		cout << *it;
	}
	cout << endl;
	for(auto it = ant.rbegin(); it != ant.rend(); it++) {
		cout << *it;
	}
	cout << endl;
	
	
}
