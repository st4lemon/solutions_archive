#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

struct pt {
	ld x, y;
	explicit pt(ld x=0, ld y=0) : x(x), y(y) { };
	pt operator*(const ld b) const {
		return pt(b*x, b*y);
	}
	pt operator/(const ld b) const {
		return pt(x/b, y/b);
	}
	pt operator-(const pt b) const {
		return pt(x - b.x, y - b.y);
	}
	pt operator+(const pt b) const {
		return pt(x + b.x, y + b.y);
	}
	ld cross(const pt p) const {
		return x*p.y - y*p.x;
	}
	ld cross(const pt x, const pt y) const {
		return (x-*this).cross(y-*this);
	}
	friend ostream& operator<<(ostream& os, pt p) {
		os << "[" << p.x << ", " << p.y << "]";
		return os;
	}
};

pair<int, pt> lineInter(const pt s1, const pt e1, const pt s2, const pt e2) {
	auto d = (e1 - s1).cross(e2 - s2);
	if (d == 0) {
		return make_pair(-(s1.cross(e1, e2) == 0), pt(0, 0));
	}
	auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
	return {1, (s1 * p + e1 * q) / d};
}

ld polygonArea(const vector<pt>& p) {
	ld ans = 0;
	for(int i = 0; i<(int)p.size(); i++) {
		const pt& cur = p[i], prev = i ? p[i-1] : p.back();
		ans += cur.cross(prev);
	}
	return fabs(ans/2);
}

vector<pt> polygonCut(const vector<pt>& poly, pt s, pt e) {
	
	vector<pt> res;
	for(int i = 0; i<(int)poly.size(); i++) {
		pt cur = poly[i], prev = i ? poly[i-1] : poly.back();
		auto a = s.cross(e, cur), b = s.cross(e, prev);
		if((a < 0) != (b < 0)) {
			res.push_back(cur + (prev - cur) * (a / (a - b)));
		}
		if (a < 0) {
			res.push_back(cur);
		}
	}
	return res;
	
}

void printFace(vector<pt>& face) {
	for(pt& p : face) {
		cout << p << " ";
	}
	cout << endl;
}


vector<pair<pt, pt>> lines;
vector<vector<pt>> faces;

bool onBoundingBox(vector<pt>& face, ld ax, ld ay, ld bx, ld by) {
	for(const pt& p : face) {
		if(p.x < ax + 100 || p.y < ay + 100 || p.x > bx - 100 || p.y > by - 100) return true;
	}
	return false; // if any intersection points lie outside the +100 bounding box, then it is a point on the bounding box. 
}

int main() {
    
    freopen("areas.in", "r", stdin);
    freopen("areas.out", "w", stdout);
	
	int N;
	cin >> N;
	
	for(int i = 0; i<N; i++) {
		ld a, b, c, d;
		cin >> a >> b >> c >> d;
		lines.emplace_back(pt(a, b), pt(c, d));
	}
	ld ax = 0, bx = 0, ay = 0, by = 0;
	for(int i = 0; i<N; i++) {
		for(int j = 0; j<i; j++) {
			auto [res, p] = lineInter(lines[i].first, lines[i].second, lines[j].first, lines[j].second);
			if(res <= 0) continue;
			ax = min(ax, p.x);
			ay = min(ay, p.y);
			bx = max(bx, p.x);
			by = max(by, p.y);
		}
	}
	ax -= 200;
	ay -= 200;
	bx += 200;
	by += 200;
	
	// out << ax << " " << ay << " " << bx << " " << by << endl;
	
	faces.emplace_back();
	faces.back().emplace_back(ax, ay);
	faces.back().emplace_back(bx, ay);
	faces.back().emplace_back(bx, by);
	faces.back().emplace_back(ax, by);
	
	for(int i = 0; i<N; i++) {
		vector<vector<pt>> nfaces;
		for(vector<pt>& poly : faces) {
			// cut both sides
			vector<pt> res1 = polygonCut(poly, lines[i].first, lines[i].second);
			vector<pt> res2 = polygonCut(poly, lines[i].second, lines[i].first);
			if(res1.size() >= 3 && polygonArea(res1) > 1e-8) {
				nfaces.push_back(res1);
			}
			if(res2.size() >= 3 && polygonArea(res2) > 1e-8) {
				nfaces.push_back(res2);
			}
		}
		faces = nfaces;
		//~ cout << i << endl;
		//~ for(vector<pt>& p : faces) {
			//~ printFace(p);
		//~ }
	}
	
	vector<ld> ans;
	for(vector<pt>& poly : faces) {
		if(onBoundingBox(poly, ax, ay, bx, by)) continue;
		ld pa = polygonArea(poly);
		if(pa <= 1e-8)  continue;
		ans.push_back(pa);
	}
	sort(ans.begin(), ans.end());
	cout << ans.size() << endl;
	for(ld& a : ans) {
		cout << fixed << setprecision(8) <<  a << endl;
	}
	
	
}