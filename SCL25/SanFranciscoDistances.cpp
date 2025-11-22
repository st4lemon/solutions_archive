#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double

void solve() {
		
	int x1, y1, x2, y2;
	char d1, d2;
	cin >> x1 >> y1 >> d1 >> x2 >> y2 >> d2;
	
	if(d1 == 'S' && d2 == 'S') {
		//~ cout << "lol" << endl;
		cout << fixed << setprecision(10) << (double)abs(x1-x2) + abs(y1-y2) << endl;
	}
	else if(d1 == 'N' && d2 == 'N') {
		//~ cout << "xd" << endl;
		double dist = (double)abs(x1-x2) + abs(y1-y2);
		int vx = min(x1, x2);
		int vy = min(y1, y2);
		if(vx + vy < 0) {
			dist += 2 * ((double)vx + vy);
			dist -= sqrt(2) * ((double)vx + vy);
		}
		cout << fixed << setprecision(10) << dist << endl;
	}
	else {
		if(d1 == 'S' && d2 == 'N') {
			swap(x1, x2);
			swap(y1, y2);
		}
		int L = -y1;
		int R = x1;
		double num = x2 / sqrt(2);
		int left = (int) num;
		int right = left + (num < 0 ? -1 : 1);
		double base = (double)x1 + y1 + y2;
		double best = 1e18;
		
		// check left
		if(L <= left && left <= R) {
			best = min(best, base + (double)fabs(left*sqrt(2) - x2));
		}
		else {
			best = min(best, min(base + (double)fabs(x2 - R * sqrt(2)), base + (double)fabs(x2 - L * sqrt(2))));
		}
		

		// check right
		if(L <= right && right <= R) {
			best = min(best, base + (double)fabs(right*sqrt(2) - x2));
		}
		else {
			best = min(best, min(base + (double)fabs(x2 - R * sqrt(2)), base + (double)fabs(x2 - L * sqrt(2))));
		}
		
		cout << fixed << setprecision(10) << best << endl;
	}
	
}

signed main() {

	
	int T; 
	cin >> T;
	
	while(T--) solve();
	
}
