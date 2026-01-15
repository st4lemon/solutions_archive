//
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct pt {
    ll x;
    ll y;
    int ind;
};

ll cross(pt one, pt two) {
    return one.x * two.y - two.x * one.y;
}

istream& operator>>(istream& is, pt& p) {
    is >> p.x >> p.y;
    return is;
}

struct cmp {
    bool operator()(const pt& one, const pt& two) {
        if(one.x == two.x) return one.y < two.y;
        return one.x > two.x;
    }
};


struct comp {
    bool operator()(const pt& one, const pt& two) {
        if(one.x * one.y == 0 && two.x * two.y == 0) {
            return one.y < two.y;
        }
        return one.x * two.y > one.y * two.x;
    }
};

ostream& operator<<(ostream& os, pt& p) {
    os << p.x << " " << p.y;
    return os;
}

pt operator-(pt one, pt two) {
    pt ret;
    ret.x = one.x - two.x;
    ret.y = one.y - two.y;
    return ret;
}

ll score(pt dish, ll x, ll y) {
    return x * dish.x + y * dish.y;
}



int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    vector<pt> dishes(N);
    vector<pt> diners(M);

    for(int i = 0; i<N; i++) {
        cin >> dishes[i];
        dishes[i].ind = i;
    }

    for(int i = 0; i<M; i++) {
        cin >> diners[i];
        diners[i].ind = i;
    }

    sort(dishes.begin(), dishes.end(), cmp());
    sort(diners.begin(), diners.end(), comp());
    /*
    cout << "dishes\n";
    for(auto p : dishes) {
        cout << p << '\n';
    }
    cout << "diners\n";
    for(auto p : diners) {
        cout << p << '\n';
    }

    cout << '\n';
    */
    vector<pt> hull;

    for(int i = 0; i<N; i++) {
        while(hull.size() >= 2) {
            int n = hull.size();
            if(cross(hull[n-1]-dishes[i], hull[n-2]-dishes[i]) > 0) {
                hull.pop_back();
            }
            else break;
        }
        hull.push_back(dishes[i]);
    }

    // for(auto p : hull) cout << p << '\n';

    vector<int> ans(M, 0);
    int curr = 0;
    int next = 1;
    bool checked = false;
    for(int i = 0; i<M; i++) {
        if(i > 0) {
            if(diners[i].x * diners[i-1].y != diners[i-1].x * diners[i].y) {
                checked = false;
                curr = next - 1;
            }
        }
        while(curr < hull.size()-1) {
            ll s1 = score(hull[curr+1], diners[i].x, diners[i].y);
            ll s2 = score(hull[curr], diners[i].x, diners[i].y);
            if(s1 > s2) {
                curr = next;
                next = curr + 1;
                checked = false;
            }
            else if (s1 == s2 && !checked) {
                int low = curr;
                int high = hull.size()-1;
                while (low < high) {
                    int m = (low + high + 1) / 2;
                    if(score(hull[m], diners[i].x, diners[i].y) == s1) {
                        low = m;
                    }
                    else high = m-1;
                }
                // cout << curr << " " << low << '\n';
                int best = curr;
                for(int k = curr+1; k<= low; k++) {
                    if(hull[k].ind < hull[best].ind) {
                        best = k;
                    }
                }
                curr = best;
                next = low + 1;
                checked = true;
                break;
            }
            else {
                break;
            }
        }
        ans[diners[i].ind] = hull[curr].ind+1;
    }

    for(int a : ans) cout << a << '\n';


}
