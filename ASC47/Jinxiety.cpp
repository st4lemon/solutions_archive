#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

void printvec(vector<int>& v) {
    for(int& a : v) {
        cout << a << " ";
    }
    cout << endl;
}

struct seg {
    int n, m;
    vector<vector<int>> a;
    vector<int> M(vector<int> &x, vector<int> &y) {
        vector<int> z(m);
        for (int i = 0; i < m; i++) {
            z[i] = max(x[i], y[i]);
        }
        return z;
    }
    seg(int _n, int _m, vector<vector<int>> &in) : n(_n), m(_m) {
        a.assign(2*_n,vector<int>(m, 0));
        for (int i = 0; i < n; i++) {
            u(i, in[i]);
        }
        // cout << "BUILT" << endl;
        //~ for(int i = 0; i < 2*_n; i++) {
        //~ printvec(a[i]);
        //~ }
    }
    void u(int pos, vector<int>& val) {
        for (a[pos += n] = val; pos /= 2;) {
            a[pos] = M(a[pos*2], a[pos*2+1]);
        }
    }
    vector<int> q(int l, int r) {
        vector<int> res(m, 0);
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2) res = M(res, a[l++]);
            if (r % 2) res = M(res, a[--r]);
        }
        return res;
    }
};


void test(int ind, bool iscol, vector<pii>& rows, vector<pii>& cols, vector<int>& ra, vector<int>& ca, int H, int W) {
    // cout << "TESTING " << ind << " " << iscol << endl;
    vector<int> v;
    pii r, c;
    if(iscol) {
        c = {ind, ind};
        r = rows[ind];
        ca[ind] = 0;
        for(int i = rows[ind].first; i<=rows[ind].second; i++) {
            v.push_back(i);
        }
    }
    else {
        r = {ind, ind};
        c = cols[ind];
        ra[ind] = 0;
        for(int i = cols[ind].first; i<=cols[ind].second; i++) {
            v.push_back(i);
        }
    }
    // cout << "yes" << endl;
    bool changed = true;
    int base = 0;
    while(changed) {
        changed = false;
        if(iscol) {
            pii nc = c;
            for(int& k : v) {
                // cout << k << endl;
                if(cols[k].first < c.first || cols[k].second > c.second) {
                    changed = true;
                    ra[k] = base + 1;
                }
                else {
                    ra[k] = base;
                }
                nc.first = min(cols[k].first, nc.first);
                nc.second = max(cols[k].second, nc.second);
            }
            v.clear();
            for(int i = nc.second; i>c.second; i--) {
                v.push_back(i);
            }
            for(int i = nc.first; i<c.first; i++) {
                v.push_back(i);
            }
            c = nc;
        }
        else {
            pii nr = r;
            for(int& k : v) {
                // cout << k << endl;
                if(rows[k].first < r.first || rows[k].second > r.second) {
                    changed = true;
                    ca[k] = base + 1;
                }
                else {
                    ca[k] = base;
                }
                nr.first = min(rows[k].first, nr.first);
                nr.second = max(rows[k].second, nr.second);
            }
            v.clear();
            for(int i = nr.second; i>r.second; i--) {
                v.push_back(i);
            }
            for(int i = nr.first; i<r.first; i++) {
                v.push_back(i);
            }
            r = nr;
        }
        // cout << c.first << " " << c.second << " - " << r.first << " " << r.second << endl;
        base++;
        iscol = !iscol;
    }


}

vector<int> minimize(vector<int>& x, vector<int>& y) {
    vector<int> z;
    for (int i = 0; i < (int)(x.size()); i++) {
        z.push_back(min(x[i], y[i]));
    }
    return z;
}


void solve(int H, int W) {

    vector<string> grid(H);
    vector<pii> rows(W, {H, -1}); // rows[i] = the range of rows that col i can reach
    vector<pii> cols(H, {W, -1}); // cols[i] = the range of cols that row i can reach.

    for(int i = 0; i<H; i++) {
        cin >> grid[i];
        for(int j = 0; j<W; j++) {
            // cout << i << " " << j << endl;
            if(grid[i][j] == '#') {
                cols[i].first = min(cols[i].first, j);
                cols[i].second = max(cols[i].second, j);
                rows[j].first = min(rows[j].first, i);
                rows[j].second = max(rows[j].second, i);
            }
        }
    }

    vector<vector<int>> visrr(H, vector<int>(H, 10000)); // starting from row i, dist to rows
    vector<vector<int>> visrc(H, vector<int>(W, 10000)); // starting from row i, dist to cols
    vector<vector<int>> viscr(W, vector<int>(H, 10000)); // starting from row i, dist to rows
    vector<vector<int>> viscc(W, vector<int>(W, 10000)); // starting from row i, dist to cols

    for(int i = 0; i<H; i++) {
        test(i, false, rows, cols, visrr[i], visrc[i], H, W);
        // cout << "H " << i << endl;
        // printvec(visrr[i]);
        // printvec(visrc[i]);
    }

    for(int i = 0; i<W; i++) {
        test(i, true, rows, cols, viscr[i], viscc[i], H, W);
        // cout << "R " << i << endl;
        // printvec(viscr[i]);
        // printvec(viscc[i]);
    }

    seg vcr(W, H, viscr);
    seg vcc(W, W, viscc);

    int ans = 0;

    for(int i = 0; i<H; i++) {
        // cout << i << endl;
        if(cols[i].first > cols[i].second) continue;
        vector<int> cr = vcr.q(cols[i].first, cols[i].second+1);
        vector<int> cc = vcc.q(cols[i].first, cols[i].second+1);
        // printvec(cr);
        // printvec(cc);
        vector<int> r = minimize(cr, visrr[i]);
        vector<int> c = minimize(cc, visrc[i]);
        // printvec(r);
        // printvec(c);

        for(int j = 0; j<H; j++) {
            // cout << r[j] << " ";
            if(r[j] == 10000) continue;
            ans = max(ans, r[j]);
        }
        for(int j = 0; j<W; j++) {
            // cout << c[j] << " ";
            if(c[j] == 10000) continue;
            ans = max(ans, c[j]);
        }
        // cout << endl;
    }

    cout << ans << endl;

}

int main() {

   freopen("jinxiety.in", "r", stdin);
   freopen("jinxiety.out", "w", stdout);

    int H, W;
    cin >> H >> W;
    while(H > 0 && W > 0) {
        solve(H, W);
        cin >> H >> W;
    }

}

