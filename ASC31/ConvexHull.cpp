//
#include <bits/stdc++.h>
using namespace std;

#define eps 1e-12
typedef long double ld;

template <class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator-() const { return P(-x, -y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    T dist2() const { return x * x + y * y; }
    T dist() const { return sqrt(dist2()) * (1 + eps); }
    P unit() const { return *this/dist(); }
    P perp() const { return P(-y, x); }
    P norm() const { return perp().unit(); }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "[" << p.x << ", " << p.y << "]";
    }
    friend istream& operator>>(istream& is, P& p) {
        return is >> p.x >> p.y;
    }
};

template <class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
    auto d = (e1-s1).cross(e2-s2);
    if (d == 0) {
        return {-(s1.cross(e1, s2) == 0), P(0, 0)};
    }
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
    return {1, (s1*p + e1*q) / d};
}

typedef Point<ld> P;

int N;
ld T;
vector<pair<P, P>> line;
vector<P> V;

vector<P> nodes;
vector<P> dir;

vector<P> upper(vector<P>& pts) {
    vector<P> hull;
    hull.push_back(pts[0]);
    hull.push_back(pts[1]);
    for(int i = 2; i<pts.size(); i++) {
        while (hull.size() >= 2 && (pts[i] - hull[hull.size() - 1]).cross(pts[i] - hull[hull.size() - 2]) >= 0) {
            hull.pop_back();
        }
        hull.push_back(pts[i]);
    }
    return hull;
}

vector<P> lower(vector<P>& pts) {
    vector<P> hull;
    hull.push_back(pts[0]);
    hull.push_back(pts[1]);
    for(int i = 2; i<pts.size(); i++) {
        while (hull.size() >= 2 && (pts[i] - hull[hull.size() - 1]).cross(pts[i] - hull[hull.size() - 2]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(pts[i]);
    }
    return hull;
}

void printhull(vector<P>& hull) {
    cout << "hull: ";
    for(P& p : hull) {
        cout << p << " ";
    }
    cout << endl;
}

ld area(vector<P>& hull) {

    // printhull(hull);
    ld ret = 0;
    for(int i = 0; i<hull.size(); i++) {
        int j = (i+1)%(hull.size());
        ret += hull[i].x * hull[j].y;
        ret -= hull[i].y * hull[j].x;
    }

    // cout << "area: " << fabs(ret)/2 << endl;

    return (fabs(ret))/2;

}

vector<P> generate(ld t) {
    vector<P> pts;
    for(int i = 0; i<nodes.size(); i++) {
        pts.push_back(nodes[i] + (dir[i]*t));
    }
    sort(pts.begin(), pts.end());

    vector<P> l = lower(pts);
    vector<P> u = upper(pts);
    l.pop_back();
    for(auto it = u.rbegin(); it != u.rend(); it++) {
        l.push_back(*it);
    }
    l.pop_back();

    return l;
};

array<ld, 3> interpolate(array<pair<ld, ld>, 3> pts) {

    ld f01 = (pts[1].second - pts[0].second)/(pts[1].first - pts[0].first);
    ld f12 = (pts[2].second - pts[1].second)/(pts[2].first - pts[1].first);
    ld f012 = (f12-f01)/(pts[2].first - pts[0].first);

    /*
     * Newton's form
     *
     * p(x) = f0 + f01(x-x0) + f012(x-x0)(x-x1)
     *   = f0 - f01 x0 + f012 x0 x1 + x * ( f01 - f012(x0 + x1)) + x^2 * f012
     *
     */

    return {
        f012,
        f01 - f012 * (pts[0].first + pts[1].first),
        pts[0].second - f01 * pts[0].first + f012 * pts[0].first * pts[1].first
    };

}

int main() {

    cin >> N;
    for(int i = 0; i<N; i++) {
        P a, b;
        ld v;
        cin >> a >> b >> v;
        // cout << a << " " << b << endl;
        line.push_back({a, b});
        V.push_back((a-b).norm()*v);
    }

    cin >> T;


//    for(int i = 0; i<N; i++) {
//        cout << line[i].first << " " << line[i].second << " " << V[i] << endl;
//    }

    for(int i = 0; i<N; i++) {
        for(int j = 0; j<i; j++) {
            auto [x, p1] = lineInter(line[i].first, line[i].second, line[j].first, line[j].second);
            auto [y, p2] = lineInter(line[i].first+V[i]*10, line[i].second+V[i]*10, line[j].first+V[j]*10, line[j].second+V[j]*10);
            if(x <= 0 || y <= 0) continue;
            // cout << nodes.size() << ": " << i << " " << j << endl;
            // cout << p1 << " " << p2 << endl;
            nodes.push_back(p1);
            dir.push_back((p2-p1)/10);
        }
    }

    int K = nodes.size();

    vector<ld> events;
    events.push_back(T);
    for(int i = 0; i<K; i++) {
        for(int j = 0; j<i; j++) {
            for(int k = 0; k<j; k++) {
                P x = nodes[j]-nodes[i];
                P dx = dir[j]-dir[i];
                P y = nodes[k]-nodes[i];
                P dy = dir[k]-dir[i];
                ld C = x.cross(y);
                ld B = x.cross(dy) + dx.cross(y);
                ld A = dx.cross(dy);
                /*
                 * solving for (x+at) (y+bt) (z+ct) is collinear
                 * (y-x + (b-a)t) cross (z-x + (c-a)t) = 0
                 * (y-x)(z-x) + (y-x)(c-a)t + (z-x)(b-a)t + (b-a)(c-a)t^2)
                 */
//                cout << i << " " << j << " " << k << endl;
//                cout << dir[i] << " " << dir[j] << " " << dir[k] << endl;
//                cout << x << " " << y << endl;
//                cout << dx << " " << dy << endl;
//                cout << "ABC " << A << " " << B << " " << C << endl;
                if(abs(A) < eps) {
                    if(abs(B) > eps && -C/B >= 0 && -C/B <= T) {
//                        cout << i << " " << j << " " << k << " -" << C << "/" << B << endl;
                        events.push_back(-C/B);
                    }
                    else {
//                        cout << i << " " << j << " " << k << endl;
                    }
                    continue;
                }
                if(4*A*C > B*B) {
                    continue;
                }
                ld m = -B / 2 / A;
                ld ac = sqrt((double) B*B - 4 * A * C) / 2 / A;
                if(m + ac >= 0 && m + ac <= T) {
//                    cout << i << " " << j << " " << k << " " << m << "+" << ac << endl;
                    events.push_back(m+ac);
                }
                if(m - ac >= 0 && m - ac <= T) {
//                    cout << i << " " << j << " " << k << " " << m << "-" << ac << endl;
                    events.push_back(m-ac);
                }
            }
        }
    }

    sort(events.begin(), events.end());

//    for(ld& e : events) {
//        cout << fixed << setprecision(16) << e << endl;
//    }
//    cout << endl;

    // build hull at time 0
    vector<P> H = generate(0);
    ld la = area(H);
    ld lt = 0;
    ld ans = 0;
    for(ld& nt : events) {
        if(nt - lt < eps) continue;
        // recompute hull at time t-eps
        // for each pair of adjacent points, use some integral to compute average change in area in that section
        ld mt = (lt + nt)/2;

        vector<P> mh = generate(mt);
        vector<P> nh = generate(nt);

        ld ma = area(mh);
        ld na = area(nh);

        array<ld, 3> c = interpolate({make_pair(lt, la), make_pair(mt, ma), make_pair(nt, na)});
        // integral of ax^2 + bx + c is ax^3/3 + bx^2/2 + cx

        ans += c[0]/3 * (nt*nt*nt - lt*lt*lt) + c[1]/2 * (nt*nt - lt*lt) + c[2] * (nt - lt);

        lt = nt;
        la = na;
        H = nh;
    }

    cout << fixed << setprecision(12) << ans/T << endl;



}

