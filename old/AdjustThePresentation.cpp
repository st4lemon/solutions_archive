// Codeforces Round 977 #C2: Adjust the Presentation (Hard)
#include <bits/stdc++.h>
using namespace std;

int N, M, Q;

void insert(vector<set<int>>& first, set<pair<int, int>>& diff, vector<int>& people, int ind) {
    if(ind <= 0 || ind >= N) return;
    if(first[people[ind]].empty()) {
        diff.insert({2*M, ind});
    }
    else if(first[people[ind-1]].empty()) {
        diff.insert({-2*M, ind});
    }
    else diff.insert({*(first[people[ind]].begin())-*(first[people[ind-1]].begin()), ind});
}

void remove(vector<set<int>>& first, set<pair<int, int>>& diff, vector<int>& people, int ind) {
    if(ind <= 0 || ind >= N) return;
    if(first[people[ind]].empty()) {
        diff.erase({2*M, ind});
    }
    else if(first[people[ind-1]].empty()) {
        diff.erase({-2*M, ind});
    }
    else diff.erase({*(first[people[ind]].begin())-*(first[people[ind-1]].begin()), ind});
}

void solve() {

    cin >> N >> M >> Q;
    vector<int> people(N);
    vector<int> ord(N+1);
    vector<int> slides(M);
    for(int i = 0; i<N; i++) {
        cin >> people[i];
        ord[people[i]] = i;
    }
    vector<set<int>> first(N+1);

    for(int i = 0; i<M; i++) {
        cin >> slides[i];
        first[slides[i]].insert(i);
    }

    bool works = true;
    for(int i = 1; i<N; i++) {
        if(first[people[i]].empty()) continue;
        if(first[people[i-1]].empty()) {
            works = false;
            break;
        }
        if(*(first[people[i]].begin()) < *(first[people[i-1]].begin())) {
            works = false;
            break;
        }
    }
    if(works) cout << "YA" << endl;
    else cout << "TIDAK" << endl;

    /*
     * how to check?
     * envision a difference array: if any of the differences are <=0 then it doesn't work
     *
     */

    set<pair<int, int>> diff; // based upon order in line, so people[i]-people[i-1]
    for(int i = 1; i<N; i++) {
        insert(first, diff, people, i);
    }

    for(int q = 0; q<Q; q++) {
        int ind, next;
        cin >> ind >> next;
        ind--;
        int prev = slides[ind];
        int prevind = ord[prev];
        int nextind = ord[next];
        // cout << "prevnext: " << prev << " " << next << endl;

        // remove diffs from before
        remove(first, diff, people, prevind);
        remove(first, diff, people, prevind+1);
        if(nextind != prevind && nextind != prevind+1) remove(first, diff, people, nextind);
        if(nextind+1 != prevind && nextind+1 != prevind+1) remove(first, diff, people, nextind+1);

        first[prev].erase(ind);
        first[next].insert(ind);

        insert(first, diff, people, prevind);
        insert(first, diff, people, prevind+1);
        if(nextind != prevind && nextind != prevind+1) insert(first, diff, people, nextind);
        if(nextind+1 != prevind && nextind+1 != prevind+1) insert(first, diff, people, nextind+1);

        if((*(diff.begin())).first < 0) {
            cout << "TIDAK" << '\n';
        }
        else cout << "YA" << '\n';
/*
        for(pair<int, int> p : diff) {
            cout << p.first << " " << p.second << endl;
        }
        for(int i = 1; i<=N; i++) {
            cout << i << ": ";
            for(int c : first[i]) {
                cout << c << " ";
            }
            cout << endl;
        }
*/
        slides[ind] = next;

    }

}

int main() {

    int T;
    cin >> T;
    for(int i = 0; i<T; i++) solve();

    cout << flush;

}

