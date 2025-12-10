#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

ld R1, R2;

ld f(ld x) {
	// cout << x << " " << 4*sqrt(R1*R1 - x*x) * sqrt(R2*R2 - x*x) << endl;
	return 4 * sqrt(R1*R1 - x*x) * sqrt(R2*R2 - x*x);
}

ld quad(ld a, ld b, const int n = 5000000) {
	ld h = (b-a) / 2 / n, v = f(a) + f(b);
	for(int i = 1; i<n*2; i++) {
		v += f(a + i*h) * (i&1 ? 4 : 2);
	}
	return v * h / 3;
}

int main() {
    
    freopen("twocyl.in", "r", stdin);
    freopen("twocyl.out", "w", stdout);
	
	cin >> R1 >> R2;
	if(R2 < R1) swap(R1, R2);
	
	cout << fixed << setprecision(8) << quad(-R1, R1) << endl;
	
}