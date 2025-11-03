// LeetCode #1622. Fancy Sequence
#include <bits/stdc++.h>
#define maxn 100001
#define MOD 1000000007

using namespace std;

class Fancy {
public:
    vector<long long> lazyadd;
    vector<long long> lazymult;
    vector<long long> values;

    /*
     * implement an addition update and a multiplication update function,
     * only needing to update lazy values when updating a smaller range
     * or getting a point query (getIndex function)
     */

    void push(int node) {
        lazymult[2*node] *= lazymult[node];
        lazymult[2*node+1] *= lazymult[node];
        lazyadd[2*node] *= lazymult[node];
        lazyadd[2*node+1] *= lazymult[node];
        lazyadd[2*node] += lazyadd[node];
        lazyadd[2*node+1] += lazyadd[node];

        lazymult[2*node] %= MOD;
        lazymult[2*node+1] %= MOD;
        lazyadd[2*node] %= MOD;
        lazyadd[2*node+1] %= MOD;

        lazymult[node] = 1;
        lazyadd[node] = 0;
    }

    void addupdate(int node, int x, int y, int i, int j, int val) {
        //if out of range, return
        if(x>j || y<i) return;
        //if i==j==x==y, update value
        //cout << x << " " << y << " " << i << " " << j << " " << val << endl;
        if(x==y) {
            values[x] *= lazymult[node];
            values[x] += lazyadd[node];
            lazymult[node] = 1;
            lazyadd[node] = 0;
            //cout << x << "-" << values[x] << endl;
            values[x] += val;
            values[x] %= MOD;
            return;
        }
        //if in range, add to lazy values
        if(x>=i && y<=j) {
            lazyadd[node] += val;
            lazyadd[node] %= MOD;
            return;
        }
        //if partially in range, push down lazy values and recurse
        push(node);
        int m = (x+y)/2;
        addupdate(2*node, x, m, i, j, val);
        addupdate(2*node+1, m+1, y, i, j, val);
    }

    void multupdate(int node, int x, int y, int i, int j, int val) {
        //if out of range, return
        if(x>j || y<i) return;
        //if x==y, update value
        if(x==y) {
            //cout << "multupdate " << x << " " << y << " " << lazymult[node] << " " << lazyadd[node] << endl;
            values[x] *= lazymult[node];
            values[x] += lazyadd[node];
            lazymult[node] = 1;
            lazyadd[node] = 0;
            values[x] *= val;
            values[x] %= MOD;
            return;
        }
        //if in range, multiply to lazy values
        if(x>=i && y<=j) {
            lazymult[node] *= val;
            lazyadd[node] *= val;
            lazymult[node] %= MOD;
            lazyadd[node] %= MOD;
            //cout << "multupdate " << x << " " << y << " " << lazymult[node] << " " << lazyadd[node] << endl;
            return;
        }
        //if partially in range, push down lazy values and recurse
        push(node);
        int m = (x+y)/2;
        multupdate(2*node, x, m, i, j, val);
        multupdate(2*node+1, m+1, y, i, j, val);
    }

    int query(int node, int x, int y, int loc) {
        //if out of range, return -1;
        if(loc < x || loc > y) return -1;
        //if x==y==loc return values[loc];
        //cout << "query " << x << " " << y << " " << lazymult[node] << " " << lazyadd[node] << endl;
        if(x==y && x==loc) {
            values[x] *= lazymult[node];
            values[x] += lazyadd[node];
            lazymult[node] = 1;
            lazyadd[node] = 0;
            values[x] %= MOD;
            return (int)(values[x]);
        }
        //if x <= loc <= y push down lazy values and recurse
        push(node);
        //cout << "pushed " << x << " " << y << endl;
        int m = (x+y)/2;
        if(loc >= x && loc <= m) return query(2*node, x, m, loc);
        else return query(2*node+1, m+1, y, loc); // (loc > m && loc <=y)
    }

    int index = 0;

    Fancy() {
        lazyadd = vector<long long>(4*maxn);
        lazymult = vector<long long>(4*maxn, 1);
        values = vector<long long>(maxn);
    }

    void append(int val) {
        //cout << index << " " << val << endl;
        values[index] = val; // don't need to update tree because it only holds additions and multiplications
        //cout << index << " " << val << endl;
        index++;
    }

    void addAll(int inc) {
        addupdate(1, 0, maxn-1, 0, index-1, inc);
    }

    void multAll(int m) {
        multupdate(1, 0, maxn-1, 0, index-1, m);
    }

    int getIndex(int idx) {
        if(idx>=index) return -1;
        return query(1, 0, maxn-1, idx);
    }
};
