// codeforces 863 problem F: Is It Flower
#include <bits/stdc++.h>
using namespace std;

#define MAXN 200005

vector<int> adj[MAXN];
int cnt[MAXN];
bool central[MAXN];
bool vis[MAXN];

int cycle(int n, bool center, int start) {
    //cout << n << " " << center << endl;
    vis[n] = true;
    for(int a : adj[n]) {
        if(vis[a]) continue;
        if(central[a]==center) {
            int ret = cycle(a, center, start)+1;
            return ret;
        }
    }
    // only if no nodes work
    if(center) return 1;

    for(int a : adj[n]) {
        if(a==start) return 1;
    }

    return MAXN;
}

bool solve() {
    int N, M;
    cin >> N >> M;

    for(int i = 0; i<N; i++) {
        cnt[i] = 0;
        central[i] = false;
        vis[i] = false;
        adj[i].clear();
    }

    for(int i = 0; i<M; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
        cnt[a]++;
        cnt[b]++;
    }

    for(int i = 0; i<N; i++) {
        if(cnt[i]==4) central[i] = true;
        else if(cnt[i]==2) central[i] = false;
        else return false;
    }

    // check center
    int K = 0;
    for(int i = 0; i<N; i++) {
        if(central[i]) {
            K = cycle(i, true, i);
            break;
        }
    }


    // check all central nodes are connected in a single cycle
    if(K<3) return false;
    for(int i = 0; i<N; i++) {
        if(central[i]) {
            if(!vis[i]) return false;
            vis[i] = false;
        }
    }

    int count = 0;
    for(int i = 0; i<N; i++) {
        //cout << i << endl;
        if(central[i]) {
            if(cycle(i, false, i)!=K) return false;
            count++;
        }
    }

    for(int i = 0; i<N; i++) {
        if(!vis[i]) return false;
    }

    //cout << count << " " << K <<  endl;
    return count==K;

}

int main() {

    int T;
    cin >> T;

    for(int i = 0; i<T; i++) {
        if(solve()) cout << "YES" << endl;
        else cout << "NO" << endl;
    }

}
/*
5


9 12
1 2
3 1
2 3
1 6
4 1
7 4
3 8
3 5
5 6
9 8
2 7
9 2


8 12
1 2
3 1
2 3
1 6
4 1
6 4
3 8
3 5
5 8
8 7
2 8
7 2


4 3
1 2
4 2
3 1


6 8
6 3
6 4
5 3
5 2
3 2
3 1
2 1
2 4


5 7
2 4
2 5
3 4
3 5
4 1
4 5
1 5
*/