// Meta Coding Puzzles Level 4 : Mathematical Art
#include <bits/stdc++.h>
using namespace std;

#define nul 3000000000000000L

// begin bit

vector<int> v;
int bitsize;
int get(int ind) {
    int sum = 0;
    ind++;
    while(ind>0) {
        sum += v[ind];
        ind -= ind & (-ind);
    }
    //for(int i = 0; i<=bitsize; i++) cout << v[i] << " ";
    //cout << "bit" << endl;
    return sum;
}

void update(int ind, int val) {
    ind++;

    while(ind<=bitsize) {
        v[ind] += val;
        ind += ind & (-ind);
    }
}


// end bit

// use multiset, upper and lower bound
// TODO: don't use multiset, use coordinate compression and bit to do this
multiset<long long> coords;

typedef pair<long long, long long> pii;
typedef pair<pii, pii> segment;
typedef pair<pii, int> ppi; // coordinate, +1 for add and -1 for remove

//vector<ppi> vpoints;

struct comp {
    bool operator() (segment o1, segment o2) {
        if(o1.first.first == o1.second.first) { // same x coordinate, vertical
            if(o1.first.first == o2.first.first) return o1.first.second < o2.first.second;
            return o1.first.first < o2.first.first;
        }
        else { // horizontal
            if(o1.first.second == o2.first.second) return o1.first.first < o2.first.first;
            return o1.first.second < o2.first.second;
        }
    }
};

struct ppisort {
    bool operator() (ppi o1, ppi o2) {
        return o1.first.second < o2.first.second;
    }
};

vector<segment> vertical;
vector<segment> horizontal;

void printseg(segment s) {
    cout << s.first.first << "|" << s.first.second << " " << s.second.first << "|" << s.second.second << endl;
}


long long getPlusSignCount(int N, vector<int> L, string D) {


    long long x = 0, y = 0; //
    for(int i = 0; i<N; i++) {
        // insert segments as (left, right) or (bottom, top)
        long long nx = x, ny = y;
        if(D[i]=='D') {
            ny -= L[i];
            vertical.push_back(make_pair(make_pair(nx, ny), make_pair(x, y)));
        }
        else if(D[i]=='L') {
            nx -= L[i];
            horizontal.push_back(make_pair(make_pair(nx, ny), make_pair(x, y)));
        }
        else if(D[i]=='U') {
            ny += L[i];
            vertical.push_back(make_pair(make_pair(x, y), make_pair(nx, ny)));
        }
        else if(D[i]=='R'){
            nx += L[i];
            horizontal.push_back(make_pair(make_pair(x, y), make_pair(nx, ny)));
        }
        x = nx;
        y = ny;
    }

    // merge horizontal segments

    sort(horizontal.begin(), horizontal.end(), comp());
    vector<segment> h;
    long long lastY = nul;
    int lastseg = -1;
    for(int i = 0; i<horizontal.size(); i++) {
        if(horizontal[i].first.second != lastY) { // moving to new row or starting search
            lastY = horizontal[i].first.second;
            if(lastseg!=-1) h.push_back(horizontal[lastseg]);
            lastseg = i;
        }
        else { // same row
            if(horizontal[i].first.first<=horizontal[lastseg].second.first) {
                horizontal[lastseg].second.first = max(horizontal[lastseg].second.first, horizontal[i].second.first); // merge segments
            }
            else {
                if(lastseg!=-1) h.push_back(horizontal[lastseg]);
                lastseg = i;
            }
        }
    }
    if(lastseg!=-1) h.push_back(horizontal[lastseg]);

    sort(vertical.begin(), vertical.end(), comp());
    long long lastX = nul;
    lastseg = -1;
    vector<segment> ver;
    for(int i = 0; i<vertical.size(); i++) {

        if(vertical[i].first.first != lastX) { // moving to new row or starting search
            lastX = vertical[i].first.first;
            if(lastseg!=-1) ver.push_back(vertical[lastseg]);
            lastseg = i;
        }
        else { // same row
            if(vertical[i].first.second<=vertical[lastseg].second.second) {
                vertical[lastseg].second.second = max(vertical[lastseg].second.second, vertical[i].second.second); // merge segment
            }
            else {
                if(lastseg!=-1) ver.push_back(vertical[lastseg]);
                lastseg = i;
            }
        }
    }
    if(lastseg!=-1) ver.push_back(vertical[lastseg]);
/*
    cout << "horizontal:" << endl;
    for(int i = 0; i<h.size(); i++) {
        printseg(h[i]);
    }
    cout << endl;

    cout << "vertical:" << endl;
    for(int i = 0; i<ver.size(); i++) {
        printseg(ver[i]);
    }
    cout << endl;
*/
    // process vertical segments into endpoints
    vector<ppi> vpoints;
    for(int i = 0; i<ver.size(); i++) {
        if(ver[i].second.second - ver[i].first.second <=1) continue; // too small of a segment to make a plus
        ver[i].first.second++;
        vpoints.push_back(make_pair(ver[i].first, 1));
        vpoints.push_back(make_pair(ver[i].second, -1));
        if(coords.find(ver[i].first.first)==coords.end()) coords.insert(ver[i].first.first);
    }

    for(int i = 0; i<h.size(); i++) {
        if(coords.find(h[i].first.first)==coords.end()) coords.insert(h[i].first.first);
        if(coords.find(h[i].second.first-1)==coords.end()) coords.insert(h[i].second.first-1);
    }
    sort(vpoints.begin(), vpoints.end(), ppisort());

/*
    for(ppi a : vpoints) {
        cout << a.first.first << "|" << a.first.second << " " << a.second << endl;
    }
*/
    // sweepline with multiset
    // horizontal segments are already sorted by y position

    vector<long long> compress;
    map<long long, int> rev;
    for(long long a : coords) {
        compress.push_back(a);
        rev.insert(make_pair(a, compress.size()-1));
        //cout << a << " " << (compress.size()-1) << endl;
    }

    long long ans = 0;
    //cout << compress.size() << endl;
    bitsize = compress.size();
    for(int i = 0; i<=bitsize; i++) v.push_back(0);
    lastY = nul;
    int nextPoint = 0;
    for(int i = 0; i<h.size(); i++) {
        //cout << i << ": " << nextPoint << endl;
        //cout << i << "- ";
        //printseg(horizontal[i]);
        if(h[i].second.first-h[i].first.first<=1) continue;
        if(h[i].first.second != lastY) { // update sweepline
            lastY = h[i].first.second;
            if(nextPoint >= vpoints.size()) break;
            while(nextPoint < vpoints.size() && vpoints[nextPoint].first.second <= lastY) {
                long long c = vpoints[nextPoint].first.first;
                //cout << c << "c" << rev.at(c) << endl;
                if(vpoints[nextPoint].second == 1) { // because we merged segments and did the ++, there will never be overlap between endpoints
                    update(rev.at(c), 1);
                }
                else {
                    //currsegs.erase(vpoints[nextPoint].first.first);
                    update(rev.at(c), -1);
                }
                nextPoint++;
                if(nextPoint >= vpoints.size()) break;
            }
        }
        int right = get(rev.at(h[i].second.first-1));
        int left = get(rev.at(h[i].first.first));
        ans += right - left;
        //cout << i << ":: " << left << " " << right << endl;
    }

    return ans;
}

int main() {

    int N = 9;
    vector<int> L = {6, 3, 4, 5, 1, 6, 3, 3, 4};
    string D = "ULDRULURD";
    cout << getPlusSignCount(N, L, D) << endl;

}