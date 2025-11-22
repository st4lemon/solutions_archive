#include <bits/stdc++.h>
using namespace std;

int main() {
	
	double val;
	while(cin >> val) {
		int num = (int)(100*(val) + 0.001);
		int m = num % 10;
		if(m == 1 || m == 2) {
			num -= m;
		}
		else if(m == 3 || m == 4) {
			num += 5 - m;
		}
		else if(m == 6 || m == 7) {
			num -= m - 5;
		}
		else if(m == 8 || m == 9) {
			num += 10 - m;
		}
		cout << fixed << setprecision(2) << 1.0 * num / 100 << endl;
	}
	
}
