#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

typedef long long ll;
typedef pair<ll, ll> pt;

int N;
pt pts[100005];

pt operator+(pt& p, ll d) {
    return {p.x + d, p.y};
}

template <int pos>
struct comp {
    bool operator()(const int& a, const int& b) const {
        const pt &p = pts[a], &q = pts[b];
        ll vp = p.x + pos * p.y, vq = q.x + pos * q.y;
        if(vp == vq) return a < b;
        return vp < vq;
    }
};

typedef comp<1> ps;
typedef comp<-1> ns;

vector<int> pset;
vector<int> nset;

ostream& operator<<(ostream& os, pt& p) {
    os << p.x << "," << p.y;
    return os;
}

bool check(int m) {
    
    // cout << "check " << m << endl;
    vector<bool> vis(N, false);

    queue<int> q;

    int pl = 0, pr = N-1;
    int nl = 0, nr = N-1;

    q.push(0);
    vis[0] = true;

    // cout << pset.size() << " " << nset.size() << endl;
    while(!q.empty()) {
        int n = q.front();
        q.pop();
        // find things within m of it
        pt top = pts[n] + m;
        pt bot = pts[n] + (-m);
        // cout << n << " " << top << " " << bot << endl;
        
        // below bot
        for(; pl <= pr; pl++) {
            if(vis[pset[pl]]) continue;
            pt& p = pts[pset[pl]];
            // cout << "below " << p << " " << p.x + p.y << endl;
            if(p.x + p.y > bot.x + bot.y) break;
            vis[pset[pl]] = true;
            q.push(pset[pl]);
        }

        for(; nl <= nr; nl++) {
            if(vis[nset[nl]]) continue;
            pt& p = pts[nset[nl]];
            // cout << "below " << p << " " << p.x + p.y << endl;
            if(p.x - p.y > bot.x - bot.y) break;
            vis[nset[nl]] = true;
            q.push(nset[nl]);
        }

        // above top
        for(; pr >= pl; pr--) {
            if(vis[pset[pr]]) continue;
            pt& p = pts[pset[pr]];
            // cout << "above " << p << " " << p.x + p.y << endl;
            if(p.x + p.y < top.x + top.y) break;
            vis[pset[pr]] = true;
            q.push(pset[pr]);
        }

        for(; nr >= nl; nr--) {
            if(vis[nset[nr]]) continue;
            pt& p = pts[nset[nr]];
            // cout << "above2 " << p << " " << p.x + p.y << endl;
            if(p.x - p.y < top.x - top.y) break;
            vis[nset[nr]] = true;
            q.push(nset[nr]);
        }

    }

    return (pr < pl) && (nr < nl);

}

int main() {

    cin.tie(0)->sync_with_stdio(0);

    cin >> N;

    for(int i = 0; i<N; i++) cin >> pts[i].x >> pts[i].y;


    for(int i = 0; i<N; i++) {
        pset.push_back(i);
        nset.push_back(i);
    }
    sort(pset.begin(), pset.end(), ps());
    sort(nset.begin(), nset.end(), ns());

    ll low = 0;
    ll high = 2e9+1;

    while(low < high) {
        int m = (low + high + 1) / 2;
        if(check(m)) {
            low = m;
        }
        else {
            high = m-1;
        }

    }

    cout << low << endl;

}