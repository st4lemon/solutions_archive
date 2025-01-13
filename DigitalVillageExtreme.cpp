// Codeforces Round 977 E3: Digital Village (Extreme Version)
#include <bits/stdc++.h>
using namespace std;

typedef pair<long long, pair<int, int>> edge;

int group(int n, vector<int>& par) {
    if(par[n] == n) return n;
    par[n] = group(par[n], par);
    return par[n];
}

void join(int a, int b, vector<int>& par, int next) {
    int pa = group(a, par);
    int pb = group(b, par);
    par[pa] = next;
    par[pb] = next;
}

long long dfs(int n, vector<edge>& children, vector<int>& served, vector<long long>& ans) {

    if(children[n].first == 0) return 0;
    // else there are two paths from left child and right child
    // add path to the edge going to that child
    int left = children[n].second.first;
    int right = children[n].second.second;
    long long res1 = dfs(left, children, served, ans);
    long long res2 = dfs(right, children, served, ans);
    long long path1 = res1 + served[left]*(children[n].first-children[left].first);
    long long path2 = res2 + served[right]*(children[n].first-children[right].first);
    // cout << n << endl;
    // cout << left << ": " << path1 << " " << right << ": " << path2 << endl;
    served[n] = served[left] + served[right];
    ans.push_back(min(path1, path2));
    return max(path1, path2);

}

void solve() {

    int N, M, P;
    cin >> N >> M >> P;

    // kruskal reconstruction tree: nodes from N to 2N-2
    // each represent an edge, there are two children nodes
    // use union find??? when we union two things together
    //      create a new parent node for both sets

    vector<int> served(2*N-1, 0);
    for(int i = 0; i<P; i++) {
        int c;
        cin >> c;
        served[c-1] = 1;
    }

    vector<edge> edges;
    for(int i = 0; i<M; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        edges.emplace_back(d, make_pair(a-1, b-1));
    }

    sort(edges.begin(), edges.end());

    vector<int> par;
    for(int i = 0; i<2*N-1; i++) {
        par.push_back(i);
    }

    int curr = 0;
    vector<edge> children; // has value of node, and two children
    for(int i = 0; i<N; i++) {
        children.emplace_back(0, make_pair(-1, -1));
    }
    for(int i = N; i<2*N-1; i++) {
        while(group(edges[curr].second.first, par) == group(edges[curr].second.second, par)) {
            curr++;
        }
        children.emplace_back(edges[curr].first, make_pair(group(edges[curr].second.first, par), group(edges[curr].second.second, par)));
        join(edges[curr].second.first, edges[curr].second.second, par, i);
    }

    vector<long long> ans;

    ans.push_back(dfs(2*N-2, children, served, ans));
    // for(int i =0; i<N; i++) cout << ans[i] << " ";
    // cout << endl;

    sort(ans.begin(), ans.end());
    for(int i = 1; i<N; i++) ans[i] += ans[i-1];
    for(int i = N-2; i>=0; i--) {
        cout << ans[i] << " ";
    }
    cout << 0 << endl;


}


int main() {

    int T;
    cin >> T;
    for(int i = 0; i<T; i++) solve();

}
