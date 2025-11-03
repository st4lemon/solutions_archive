//
#include <bits/stdc++.h>
using namespace std;

int N, Q;
void insert(int x, int val, vector<int>& tree) {
    while(x <= N) {
        tree[x] += val;
        x += (x & -x);
    }
}

int query(int x, vector<int>& tree) {
    int sum = 0;
    while(x > 0) {
        sum += tree[x];
        x -= (x & -x);
    }
    return sum;
}

int main() {

    cin >> N >> Q;

    vector<int> levels(N+1);
    for(int i = 0; i<N; i++) cin >> levels[i+1];

    vector<vector<int>> queries(N+1);
    vector<bool> ans(Q, false);
    vector<pair<int, int>> qq;

    for(int i = 0; i<Q; i++) {
        int a, b;
        cin >> a >> b;
        qq.emplace_back(a, b);
        queries[a].push_back(i);
    }

    vector<int> tree(N+1, 0);


    for(int i = 1; i<=N; i++) {
        // binary search for lowest k such that you fight
        int low = 1;
        int high = N+1;
        while(low < high) {
            int m = (low+high)/2;
            if(query(m, tree)/m < levels[i]) {
                high = m;
            }
            else {
                low = m+1;
            }
        }
        if(low == N+1) {
            continue;
        }
        insert(low, 1, tree);
        for(int q : queries[i]) {
            int a = qq[q].first;
            int b = qq[q].second;
            // cout << a << " " << b << " " << query(b, tree) << endl;
            if(low <= b) ans[q] = true;
        }
    }

    for(int i = 0; i<Q; i++) {
        if(ans[i]) cout << "YES\n";
        else cout << "NO\n";

    }
    cout << flush;

}
 
