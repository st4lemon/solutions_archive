//
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pt;

pt pts[1005];

vector<pt> ans;

ostream& operator<<(ostream& os, pt& p) {
    os << "[" << p.first << " " << p.second << "]";
    return os;
}

pt operator-(pt p, pt q) {
    return {p.first - q.first, p.second - q.second};
}

ll cross(pt p, pt q) {
//    cout << p << " " << q << " = " << p.first * q.second - p.second * q.first << endl;
    return p.first * q.second - p.second * q.first;
}

void rec(vector<pt>& v) { // v holds {index, degree} pairs

//    int a;
//    cin >> a;

    if(v.size() == 2) {
//        cout << "edge - " << min(v[0].first, v[1].first) << " " << max(v[0].first, v[1].first) << endl;
        ans.emplace_back(min(v[0].first, v[1].first)+1, max(v[0].first, v[1].first)+1);
        return;
    }

    int n = v.size();

    // find high degree node
    int best = 0;
    for(int i = 1; i<n; i++) {
        if(v[i].second > v[best].second) {
            best = i;
        }
    }

    pt b = v[best];
//    cout << "best: " << b << endl;

    // sort around this point
    sort(v.begin(), v.end(), [&](auto& x, auto& y) {
        if(x == b) return false;
        if(y == b) return true;
        pt p = pts[x.first] - pts[b.first], q = pts[y.first] - pts[b.first];
        return atan2l(p.second, p.first) < atan2l(q.second, q.first);
    });

//    for(pt& p : v) {
//        cout << p << " ";
//    }
//    cout << endl;

    // split
    n--;
    int left = 0;
    int right = 0;
    int cnt = 0;
    int deg = 0;
    for(; left<n; left++) {
        while(cnt == 0 || cross(pts[v[left].first] - pts[b.first], pts[v[right].first] - pts[b.first]) > 0) {
            deg += v[right].second;
            cnt++;
            right++;
            right %= n;
        }
//        cout << left << " " << right << " " << cnt << " " << deg << endl;
        if(2*cnt <= deg || 2*cnt >= deg + b.second) {
            deg -= v[left].second;
            cnt--;
            continue;
        }
        break;
    }
    if(left == n) return;

    cnt = 0;
    deg = 0;
    vector<pt> one;
    vector<pt> two;
//    cout << "rec - ";
    for(int i = left; i != right; i++, i %= n) {
        cnt++;
        deg += v[i].second;
        one.push_back(v[i]);
//        cout << v[i] << " ";
    }
    int rem = 2*cnt - deg;
    one.emplace_back(b.first, rem);
//    cout << one.back() << " | ";
    for(int i = right; i != left; i++, i %= n) {
        two.push_back(v[i]);
//        cout << v[i] << " ";
    }
    two.emplace_back(b.first, v[n].second - rem);
//    cout << two.back() << endl;

    rec(one);
    rec(two);


}

int main() {

    freopen("roads.in", "r", stdin);
    freopen("roads.out", "w", stdout);

    int N;
    cin >> N;

    /*
     *
     * idea:
     *   find highest degree node in list
     *   sort nodes by angle around this node
     *   sweepline, find a partition so that sum of degrees = 2n - 2 (with some fudging of the split node)
     *
     */

    vector<pt> yes;

    for(int i = 0; i<N; i++) {
        cin >> pts[i].first >> pts[i].second;
        int a;
        cin >> a;
        yes.emplace_back(i, a);
    }

    rec(yes);

    sort(ans.begin(), ans.end());
    for(auto& [x, y] : ans) {
        cout << x << " " << y << endl;
    }

}
