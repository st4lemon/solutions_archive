// ed codeforces 146 problem E: Chain Chips
#include<bits/stdc++.h>
using namespace std;

#define MAXN 200005
#define MAX 2000000000000000000

class Tree {

public:
/*
    struct thing {
        long long arr[2][2] = {{MAX, MAX}, {MAX, MAX}};
        thing() {

        }
        thing(const thing& o) {
            for(int i = 0; i<2; i++) for(int j = 0; j<2; j++) arr[i][j] = o[i][j];
        }
        thing& operator=(const thing& o) {
            if(this==(&o)) return(*this);
            for(int i = 0; i<2; i++) for(int j = 0; j<2; j++) arr[i][j] = o[i][j];
        }
    };
*/
    vector<long long**> tree;
    int size;

    Tree(vector<int>& val, int s) : tree(4*s, 0), size(s) {
        build(1, 0, s-1, val);
    }

    void build(int node, int x, int y, vector<int>& val) {
        tree[node] = new long long*[2];
        tree[node][0] = new long long[2];
        tree[node][1] = new long long[2];
        if(x==y) {
            tree[node][1][1] = val[x];
            tree[node][0][0] = 0;
            tree[node][0][1] = MAX;
            tree[node][1][0] = MAX;
            return;
        }
        int m = (x+y)/2;
        build(2*node, x, m, val);
        build(2*node+1, m+1, y, val);
        for(int i = 0; i<2; i++) {
            for(int j = 0; j<2; j++) {
                tree[node][i][j] = MAX;
                if(tree[2*node][i][1] != MAX && tree[2*node+1][1][j] != MAX) {
                    tree[node][i][j] = min(tree[node][i][j], tree[2*node][i][1] + tree[2*node+1][1][j]);
                }
                if(tree[2*node][i][0] != MAX && tree[2*node+1][1][j] != MAX) {
                    tree[node][i][j] = min(tree[node][i][j], tree[2*node][i][0] + tree[2*node+1][1][j]);
                }
                if(tree[2*node][i][1] != MAX && tree[2*node+1][0][j] != MAX) {
                    tree[node][i][j] = min(tree[node][i][j], tree[2*node][i][1] + tree[2*node+1][0][j]);
                }
            }
        }
    }

    void update(int loc, int num) {
        update(1, 0, size-1, loc, num);
    }

    void update(int node, int x, int y, int loc, int num) {
        //cout << x << " " << y << " " << loc << "-" << num << endl;
        if(x>loc || y<loc) return;
        if(x==y && x==loc) {
            tree[node][1][1] = num;
            return;
        }
        int m = (x+y)/2;
        update(2*node, x, m, loc, num);
        update(2*node+1, m+1, y, loc, num);
        for(int i = 0; i<2; i++) {
            for(int j = 0; j<2; j++) {
                tree[node][i][j] = MAX;
                if(tree[2*node][i][1] != MAX && tree[2*node+1][1][j] != MAX) {
                    tree[node][i][j] = min(tree[node][i][j], tree[2*node][i][1] + tree[2*node+1][1][j]);
                }
                if(tree[2*node][i][0] != MAX && tree[2*node+1][1][j] != MAX) {
                    tree[node][i][j] = min(tree[node][i][j], tree[2*node][i][0] + tree[2*node+1][1][j]);
                }
                if(tree[2*node][i][1] != MAX && tree[2*node+1][0][j] != MAX) {
                    tree[node][i][j] = min(tree[node][i][j], tree[2*node][i][1] + tree[2*node+1][0][j]);
                }
            }
        }
    }

    long long query(int left, int right) {
        return query(1, 0, size-1, left, right)[1][1];
    }

    long long** query(int node, int x, int y, int n, int m) {
        long long** ret = new long long*[2];
        ret[0] = new long long[2];
        ret[1] = new long long[2];
        if(x>m|| y<n || x>y) {
            for(int a = 0; a<2; a++) for(int b = 0; b<2; b++) ret[a][b] = MAX;
            return ret;
        }
        if(x>=n && y<=m) {
            return tree[node];
        }
        int mid = (x+y)/2;
        long long** q1 = query(2*node, x, mid, n, m);
        long long** q2 = query(2*node+1, mid+1, y, n, m);

        for(int i = 0; i<2; i++) {
            for(int j = 0; j<2; j++) {
                if(q1[i][1] != MAX && q2[1][j] != MAX) {
                    ret[i][j] = min(ret[i][j], q1[i][1] + q2[1][j]);
                }
                if(q1[i][0] != MAX && q2[1][j] != MAX) {
                    ret[i][j] = min(ret[i][j], q1[i][0] + q2[1][j]);
                }
                if(q1[i][1] != MAX && q2[0][j] != MAX) {
                    ret[i][j] = min(ret[i][j], q1[i][1] + q2[0][j]);
                }
            }
        }
        delete[] ret[0];
        delete[] ret[1];
        delete[] ret;
        return ret;
    }

    ~Tree(){
        for(long long** a : tree) {
            if(a==0) continue;
            delete[] a[0];
            delete[] a[1];
            delete[] a;
        }
    }

};


int main() {

    int N;
    cin >> N;

    vector<int> diff;
    for(int i = 0; i<N-1; i++) {
        int a;
        cin >> a;
        diff.push_back(a);
    }

    Tree t(diff, N-1);



    // solution idea
    // segment tree
    // (a, b) = minimum cost for all 4 endpoint cases (both taken, left taken, right taken, none taken) in a 2x2 matrix
    //
    // do a point update every query, then requery the whole tree for the both taken case

    int Q;
    cin >> Q;

    for(int i = 0; i<Q; i++) {
        //cout << i << "-----" << Q << " ";
        int a, b;
        cin >> a >> b;
        t.update(a-1, b);
        cout << 2*t.query(0, N-1) << endl;
    }

    //cout << "done" << endl;

    return 0;
}
/*
 __ _    __    _    __ __
 12 6 12 15 20 8 17 12 15 = 68
 __ _    __    _    __ __
 12 6 12 10 20 8 17 12 15 = 63      decreasing something already in the sequence: no change
 __ _    __    _ _    __
 12 6 12 10 20 8 3 12 15 = 54       decreasing something outside the sequence: check if it helps
 __ _    __    __ _    __
 12 6 12 10 20 14 3 12 15 = 60      increasing something inside the sequence: check if you have to switch
 __ _    __    __ _    _
 12 6 12 10 20 14 3 12 9 = 54
 __    __    __    _    _
 12 10 12 10 20 14 3 12 9 = 56
 __    _    __    _    _
 12 10 5 10 20 14 3 12 9 = 49
 __    _    __    _    _
 12 10 5 11 20 14 3 12 9 = 49       increasing something outside the sequence: no change
 __    _    __    __    _
 12 10 5 11 20 14 11 12 9 = 57

 idea: binary search with fenwick trees?






 */