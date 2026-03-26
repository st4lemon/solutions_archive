#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pt;

int N;

ll sgn(ll x) { return (x>0) - (x<0); }

bitset<100> isect[400][400];
pt pts[100][4];

ll cross(pt& p, pt& q, pt& r) {
    pt a = {q.first - p.first, q.second - p.second};
    pt b = {r.first - p.first, r.second - p.second};
    return a.first * b.second - a.second * b.first;
}

bool rec(bitset<100> msk) {
    // for(int i = 0; i<8; i++) cout << msk[i];
    // cout << endl;
    if(msk.count() == 1) return true;
    for(int i = 0; i<N; i++) {
        if(!msk[i]) continue;
        for(int j= i; j<N; j++) {
            if(!msk[j]) continue;
            for(int a = 0; a<4; a++) {
                for(int b = 0; b<4; b++) {
                    if((msk & isect[4*i+a][4*j+b]).count()) {
                        continue;
                    }
                    // split into two
                    bitset<100> nxt1, nxt2;
                    for(int k = 0; k<N; k++) {
                        if(!msk[k]) continue;
                        int val = sgn(cross(pts[i][a], pts[j][b], pts[k][0]));
                        val += sgn(cross(pts[i][a], pts[j][b], pts[k][1]));
                        val += sgn(cross(pts[i][a], pts[j][b], pts[k][2]));
                        if(val > 0) {
                            nxt1[k] = true;
                        }
                        else {
                            nxt2[k] = true;
                        }
                    }
                    if(nxt1 == 0 || nxt2 == 0) continue;
                    // cout << i << " " << j << " " << a << " " << b << endl;
                    return rec(nxt1) && rec(nxt2);

                }
            }
        }
    }
    return false;
}

int main() {

    cin >> N;
    for(int i = 0; i<N; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        pts[i][0] = {a, b};
        pts[i][1] = {a, d};
        pts[i][2] = {c, d};
        pts[i][3] = {c, b};
    }

    for(int i = 0; i<N; i++) {
        for(int a = 0; a<4; a++) {
            for(int j = i; j<N; j++) {
                for(int b = 0; b<4; b++) {
                    pt p = pts[i][a];
                    pt q = pts[j][b];

                    for(int k = 0; k<N; k++) {
                        for(int c = 0; c<4; c++) {
                            for(int d = 0; d<c; d++) {
                                if(sgn(cross(p, q, pts[k][c])) * sgn(cross(p, q, pts[k][d])) == -1) {
                                    isect[4*i+a][4*j+b][k] = true;
                                    break;
                                }
                            }
                        }
                    }

                }
            }
        }
    }

    bitset<100> init;
    for(int i = 0; i<N; i++) init[i] = true;

    if(rec(init)) {
        cout << N-1 << endl;
    }
    else {
        cout << "impossible" << endl;
    }

}