#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

#define eps 1e-8

typedef long double ld;
typedef long long ll;
typedef pair<ll, ll> pt;
typedef pair<ld, ld> pd;

pd operator-(pd p, pd q) {
    return {p.x - q.x, p.y - q.y};
}

pd operator+(pd p, pd q) {
    return {p.x - q.x, p.y - q.y};
}

pd operator*(pd p, ld d) {
    return {p.x * d, p.y * d};
}

ld dist2(pd p) {
    return p.x*p.x + p.y*p.y;
}

pt pts[3000];

void solve(int N) {

    map<array<ll, 3>, int> mp;

    for(int i = 0; i<N; i++) {
        cin >> pts[i].x >> pts[i].y;
        ll a = dist2(pts[i]);
        for(int j = 0; j<i; j++) {
            ll A = a;
            ll b = dist2(pts[j]);
            ll c = dist2(pts[j]-pts[i]);
            if(A > b) swap(A, b);
            mp[{A, b, c}]++;
            // cout << i << " " << j << " " << a << " " << b << " " << c << endl;
        }
    }



    int M;
    cin >> M;
    for(int i = 0; i<M; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        if(a > b) swap(a, b);
        cout << mp[{a, b, c}] << endl;
    }

}

int main() {
    
    freopen("astronomy.in", "r", stdin);
    freopen("astronomy.out", "w", stdout);

    int N;
    cin >> N;
    while(N != 0) {
        solve(N);
        cin >> N;
    }

}