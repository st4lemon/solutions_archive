// LeetCode #2286. Booking Concert Tickets in Groups
#include <bits/stdc++.h>

using namespace std;

class SegmentTree {
public:
    int N;
    vector<int> mintree; // 4*N
    vector<long long> sumtree;
    vector<int> values; // N

    SegmentTree(int n, vector<int>& v) {
        N = n;
        values = v;
        mintree = vector<int>(4*n);
        sumtree = vector<long long>(4*n);
        build(1, 0, N-1);
    }

    void build(int node, int x, int y) { // minmintree
        //cout << x << " " << y << endl;
        if(x==y) {
            mintree[node] = values[x];
            sumtree[node] = values[x];
            return;
        }
        int m = (x+y)/2;
        build(2*node, x, m);
        build(2*node+1, m+1, y);
        mintree[node] = min(mintree[2*node], mintree[2*node+1]);
        sumtree[node] = sumtree[2*node] + sumtree[2*node+1];
    }

    int minquery(int node, int x, int y, int i, int j) {
        if(x>y) return 0x7FFFFFFF;
        if(x>j || y<i) return 0x7FFFFFFF;
        if(x >= i && y <= j) return mintree[node];
        int m = (x+y)/2;
        int val = min(minquery(2*node, x, m, i, j), minquery(2*node+1, m+1, y, i, j));
        return val;
    }

    long long sumquery(int node, int x, int y, int i, int j) {
        if(x>y) return 0;
        if(x>j || y<i) return 0;
        if(x >= i && y <= j) return sumtree[node];
        int m = (x+y)/2;
        long long val = sumquery(2*node, x, m, i, j) + sumquery(2*node+1, m+1, y, i, j);
        return val;
    }

    void update(int node, int x, int y, int loc, int val) { // point updates only
        if(x==loc && y==loc) {
            mintree[node] += val;
            sumtree[node] += val;
            values[loc] += val;
            return;
        }
        if(x > loc || y < loc) return; // loc not in range
        int m = (x+y)/2;
        update(2*node, x, m, loc, val);
        update(2*node+1, m+1, y, loc, val);
        mintree[node] = min(mintree[2*node], mintree[2*node+1]);
        sumtree[node] = sumtree[2*node] + sumtree[2*node+1];
    }

    SegmentTree() {

    }

};

class BookMyShow {
public:
    SegmentTree tree;
    vector<int> seats;
    long long total;
    int N, M, minrow = 0;

    BookMyShow(int n, int m) {
        N = n;
        M = m;
        total = ((long long)N) * M;
        seats = vector<int>(N);
        //cout << 3 << endl;
        tree = SegmentTree(n, seats);
        //cout << 4 << endl;
    }

    void updateMinRow() {
        while(tree.values[minrow]==M) {
            if(minrow==N-1) break;
            minrow++;
        }
    }

    /*
     * steps:
     * 1. bsearch using segment tree as comparison function (pick leftmost whenever possible)
     * 2. insert value
     * 3. update
     */
    vector<int> gather(int k, int maxRow) {
        //cout << k << " " << maxRow << endl;
        int index = bsearch(minrow, maxRow, M-k);
        vector<int> ret;
        if(index==-1) return ret;
        ret.push_back(index);
        ret.push_back(tree.values[index]);
        tree.update(1, 0, N-1, index, k);
        updateMinRow();
        return ret;
    }

    int bsearch(int x, int y, int val) { // val is the maximum amount of seats that can be taken for a "valid" row
        int m = (x+y)/2;
        //cout << x << " " << y << " " << val << endl;
        if(x==y) {
            if(tree.values[x]>val) return -1;
            return x;
        }
        int a = tree.minquery(1, 0, N-1, x, m);
        int b = tree.minquery(1, 0, N-1, m+1, y);

        if(a > val) {
            if(b > val) {
                return -1;
            }
            return bsearch(m+1, y, val);
        }

        return bsearch(x, m, val);

    }

    /*
     * steps
     * 1. start at minrow
     * 2. fill if valid
     * 3. for every row that gets fully filled, update minrow and update segtree
     *      (updating fills ADDS factor of NlogN at most, so its okay)
     */
    bool scatter(int k, int maxRow) {
        int i = minrow;
        long long rem = ((long long)M)*(maxRow+1) - tree.sumquery(1, 0, N-1, 0, maxRow);
        //cout << k << " " << maxRow << " " << rem << endl;
        if(rem < k) return false;
        while(i<N && M-tree.values[i] < k) {
            k -= M-tree.values[i];
            tree.update(1, 0, N-1, i, M-tree.values[i]);
            i++;
        }
        tree.update(1, 0, N-1, i, k);
        updateMinRow();
        return true;
    }
};