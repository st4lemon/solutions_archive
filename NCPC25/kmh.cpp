#include <bits/stdc++.h>
using namespace std;

int main() {
	
	int N;
	cin >> N;
	string s;
	
	int mx = 0;
	for(int i = 0; i<N; i++) {
		cin >> s;
		if(s == "/") {
			cout << mx << endl;
		}
		else {
			int n = stoi(s);
			cout << n << endl;
			mx = max(mx, 10*(n/10+1));
		}
	}	
	
}

