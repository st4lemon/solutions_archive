#include <bits/stdc++.h>
using namespace std;

void solve() {
	
	int x1, y1, x2, y2, x3, y3;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	int d1 = x1*x1 + y1*y1;
	int d2 = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
	int d3 = (x3-x1)*(x3-x1) + (y3-y1)*(y3-y1);
	
	if(d2 < d1 && d3 < d1) {
		cout << "YES" << endl;
	}
	else if(d2 > d1 || d3 > d1) {
		cout << "NO" << endl;
	}
	else if(d2 == d1 && d3 == d1) {
		cout << "NO" << endl;
	}
	else {
		if(d2 == d1) {
			if(x1 * (y2-y1) - (x2 - x1) * y1 == 0) {
				cout << "NO" << endl;
			}
			else {
				cout << "YES" << endl;
			}
		}
		else {
			if(x1 * (y3-y1) - (x3 - x1) * y1 == 0) {
				cout << "NO" << endl;
			}
			else {
				cout << "YES" << endl;
			}
		}
	}
	
	
	
}

int main()  {
	
	int T;
	cin >> T;
	while(T--) solve();
	
}
