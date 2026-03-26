//
#include <bits/stdc++.h>
using namespace std;

typedef pair<double, double> pt;
typedef long long ll;

int N, K;
pt pts[100005]; // pts[x] = point of frequency x
bool found[100005];

ll rd[100005]; // reading
int rf[100005]; // freq

int lft[100005];
int rht[100005];

pt ans[100005];


bool circleInter(pt a, pt b, double r1, double r2, pair<pt, pt>& out) {
    if (a == b) { assert(r1 != r2); return false; }
    pt vec = {b.first - a.first, b.second - a.second};
    double d2 = vec.first*vec.first + vec.second * vec.second;
    double sum = r1 + r2;
    double dif = r1 - r2;
    double p = (d2 + r1*r1 - r2*r2)/(d2 * 2), h2 = r1*r1 - p*p*d2;
    if (sum*sum < d2 || dif*dif > d2) return false;
    pt mid = {vec.first * p + a.first, vec.second * p + a.second};
    double m = sqrt(fmax(0, h2) / d2);
    pt per = {-vec.second * m, vec.first * m};
    out = {{mid.first + per.first, mid.second + per.second}, {mid.first - per.first, mid.second - per.second} };
    return true;
}

int main() {

    cin >> N >> K;

    for(int i = 0; i<K; i++) {
        double a, b;
        int freq;
        cin >> a >> b >> freq;
        freq--;
        found[freq] = true;
        pts[freq] = {a, b}; //
    }

    for(int i = 0; i<N; i++) {
        cin >> rd[i] >> rf[i];
        rf[i]--;
    }

    // l, r stores positions
    int num = -1;
    for(int i = 0; i<N; i++) {
        if(found[rf[i]]) { // if we found the frequency of position i
            num = i;
        }
        lft[i] = num;
    }

    num = N;
    for(int i = N-1; i>=0; i--) {
        if(found[rf[i]]) {
            num = i;
        }
        rht[i] = num;
    }

    for(int i = 0; i<N; i++) {
        // calculate the correct circle intersection
        if(found[rf[i]]) continue;

        double maxr = 1e18;
        if(lft[i] != -1) {
            auto [x, y] = pts[rf[lft[i]]];
            double rad = (rd[i]-x)*(rd[i]-x) + y*y;
            maxr = min(maxr, rad);
        }
        if(rht[i] != N) {
            auto [x, y] = pts[rf[rht[i]]];
            double rad = (rd[i]-x)*(rd[i]-x) + y*y;
            maxr = min(maxr, rad);
        }
//        cout << maxr << " " << lft[i] << " " << rht[i] << endl;
        // must be outside of the adjacent gemstones
        // 1. check if the maximum point is in either circle

        bool works = true;
        if(lft[i] != -1) {
            auto [x, y] = pts[rf[lft[i]]];
            double rad = (rd[i] - rd[lft[i]])*(rd[i] - rd[lft[i]]) + maxr;
            double rad2 = (rd[lft[i]]-x)*(rd[lft[i]]-x) + y*y; //
//            cout << x << " " << y << endl;
//            cout << rd[i] << " " << rd[lft[i]] << endl;
//            cout << (rd[i] - rd[lft[i]]) << endl;
//            cout << (rd[i] - rd[lft[i]])*(rd[i]-rd[lft[i]]) << endl;
//            cout << rad << " " << rad2 << endl;
            if(rad < rad2) works = false;
        }
        if(rht[i] != N) {
            auto [x, y] = pts[rf[rht[i]]];
            double rad = (rd[i] - rd[rht[i]])*(rd[i] - rd[rht[i]]) + maxr;
            double rad2 = (rd[rht[i]]-x)*(rd[rht[i]]-x) + y*y;
//            cout << rd[i] << " " << rd[rht[i]] << endl;
//            cout << rad << " " << rad2 << endl;
            if(rad < rad2) works = false;
        }

        // 2. If in some circle, find better circle intersection?
        if(works) {
            ans[rf[i]] = {rd[i], -sqrt(maxr)};
            continue;
        }

        pt best = {rd[i], 0};
        if(lft[i] != -1) {
            pair<pt, pt> out;
            auto [x, y] = pts[rf[lft[i]]];
            double rad2 = (rd[lft[i]]-x)*(rd[lft[i]]-x) + y*y;
            if(circleInter({rd[i], 0}, {rd[lft[i]], 0}, sqrt(maxr), sqrt(rad2), out)) {
                if(out.first.second < best.second) {
                    best = out.first;
                }
                if(out.second.second < best.second) {
                    best = out.second;
                }
            }
        }
        if(rht[i] != N) {
            pair<pt, pt> out;
            auto [x, y] = pts[rf[rht[i]]];
            double rad2 = (rd[rht[i]]-x)*(rd[rht[i]]-x) + y*y;
            if(circleInter({rd[i], 0}, {rd[rht[i]], 0}, sqrt(maxr), sqrt(rad2), out)) {
                if(out.first.second < best.second) {
                    best = out.first;
                }
                if(out.second.second < best.second) {
                    best = out.second;
                }
            }
        }

        ans[rf[i]] = best;

    }

    cout << fixed << setprecision(8);
    for(int i = 0; i<N; i++) {
        if(found[i]) continue;
        cout << i+1 << " " << ans[i].second << endl;
    }





}

