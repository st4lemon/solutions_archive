//
#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<int> adj[1005];
int color[1005] = {0}; // 0 default, color = 1, 2, 3;
int CEO;

// for rec()
int visited[1005] = {0};
int viscount = 0;
vector<int> in;

// SCC stuff
vector<int> sadj[3005]; // sadj[i] = node i/3, color i%3 + 1;
vector<int> radj[3005];
bool blocked[3005] = {0}; // blocked[i] = true -> color i%3+1 cannot be used on node i/3
vector<vector<int>> SCCS;
int which[3005];

int countblocked(int n) {
    int ret = 0;
    for(int j = 0; j<3; j++) {
        if(!blocked[3*n+j]) ret++;
    }
    return ret;
}

stack<int> post;
int sccount;

void dfs1(int n, vector<bool>& vis) {
    vis[n] = true;
    for(int a : sadj[n]) {
        if(vis[a]) continue;
        dfs1(a, vis);
    }
    post.push(n);
}

void dfs2(int n) {
    // cout << sccount << " " << n/3 << "-" << n%3+1 << endl;
    which[n] = sccount;
    SCCS.back().push_back(n);
    for(int a : radj[n]) {
        if(which[a]==-1) dfs2(a);
    }
}


void make() {
    SCCS.clear();
    vector<bool> vis(3*N);
    for(int i = 0; i<3*N; i++) if(color[i/3]!=0 || blocked[i]) vis[i] = true;
    for(int i = 0; i<3*N; i++) {
        if(!vis[i]) dfs1(i, vis);
    }
    sccount = 0;
    while(!post.empty()) {
        int n = post.top();
        post.pop();
        if(which[n]==-1) {
            SCCS.emplace_back();
            // cout << "yeet" << endl;
            dfs2(n);
            sccount++;
        }
    }
    // SCC alg here
}

bool SCC() {
    // review cs130a for this?
    // cout << "SCC" << endl;
    for(int i = 0; i<3*N; i++) which[i] = -1;

    bool ret = true;
    for(int i = 0; i<N; i++) {
        if(color[i]!=0) {
            ret = false;
            break;
        }
    }
    if(ret) return true;

    make();

    /*
    vector<vector<bool>> sccadj(SCCS.size(), vector<bool>(SCCS.size()));
    vector<int> indeg(SCCS.size(), 0);
    for(int i = 0; i<3*N; i++) {
        // cout << i/3 << "-" << i%3+1 << " " << which[i] << endl;
        // which[i] = scc that i is in
        if(which[i]==-1) continue;
        for(int j : sadj[i]) {
            // cout << j/3 << "-" << j%3+1 << " " << which[j] << " ";
            if(which[i]==which[j]) continue;
            if(which[j]==-1) continue;
            sccadj[which[i]][which[j]] = true;
            indeg[which[j]]++;
        }
        // cout << endl;
    }

    queue<int> q;
    vector<int> sorder; // toposort ordering
    for(int i = 0; i<SCCS.size(); i++) {
        if(indeg[i]==0) {
            q.push(i);
        }
    }
    while(!q.empty()) {
        int n = q.front();
        sorder.push_back(n);
        indeg[n]--;
        q.pop();
        for(int i = 0; i<SCCS.size(); i++) {
            if(sccadj[n][i]) {
                indeg[i]--;
                if(indeg[i]==0) q.push(i);
            }
        }
    }
*/
    for(int i = 0; i<N; i++) {
        if(which[3*i] == which[3*i+1] && which[3*i]!=-1) {
            // cout << i << endl;
            return false;
        }
        if(which[3*i] == which[3*i+2] && which[3*i]!=-1) {
            // cout << " " << i << endl;
            return false;
        }
        if(which[3*i+2] == which[3*i+1] && which[3*i+1]!=-1) {
            // cout << "  " << i << endl;
            return false;
        }
    }

    // cout << "checked" << endl;

    for(int i = 0; i<N; i++) {
        if(color[i]==0) {
            int best = which[3*i];
            int col = 1;
            for(int j = 1; j<3; j++) {
                if(which[3*i+j] > best) {
                    best = which[3*i+j];
                    col = j+1;
                }
            }
            if(best==-1) return false;
            color[i] = col;
        }
        for(int a : adj[i]) {
            if(color[a]==color[i]) return false;
        }
        // cout << i << endl;
    }

    // cout << "yes" << endl;
    return true;
}

bool solve1() {
    queue<int> q;
    for(int i = 0; i<N; i++) {
        if(color[i]!=0) {
            for(int j : adj[i]) {
                if(color[i]==color[j]) {
                    // cout << i << " " << j << " color" << endl;
                    return false;
                }
            }
            continue;
        }
        if(countblocked(i)==0) {
            // cout << i << " blocked" << endl;
            return false;
        }
        if(countblocked(i)==1) {
            for(int j = 0; j<3; j++) {
                if(!blocked[3*i+j]) {
                    color[i] = j+1;
                    break;
                }
            }
            q.push(i);
            // cout << i << endl;
        }
    }
    while(!q.empty()) {
        int n = q.front();
        q.pop();
        for(int a : adj[n]) {
            if(color[a]==color[n]) {
                // cout << n << " contradicts " << a << endl;
                return false;
            }
            if(color[a]!=0) continue;
            blocked[3*a+color[n]-1] = true;
            int count = countblocked(a);
            if(count==1) {
                for(int j = 0; j<3; j++) {
                    if(!blocked[3*a+j]) {
                        color[a] = j+1;
                        break;
                    }
                }
                q.push(a);
            }
        }
    }
    return true;
}

void printsadj() {
    for(int i = 0; i<3*N; i++) {
        cout << i/3 << "-" << i%3+1 << " -> ";
        for(int a : sadj[i]) {
            cout << a/3 << "-" << a%3+1 << " ";
        }
        cout << endl;
    }
}

void printradj() {
    for(int i = 0; i<3*N; i++) {
        cout << i/3 << "-" << i%3+1 << " -> ";
        for(int a : radj[i]) {
            cout << a/3 << "-" << a%3+1 << " ";
        }
        cout << endl;
    }
}

bool generate() {
    for(int i = 0; i<3*N; i++) {
        sadj[i].clear();
        radj[i].clear();
    }

    if(!solve1()) { // recursively get rid of things with 1 blocked
        // cout << "solve no worky" << endl;
        return false;
    }

    // sanity check

    for(int i = 0; i<N; i++) {
        if(color[i]!=0) {
            for(int a : adj[i]) {
                blocked[3*a + color[i]-1] = true;
            }
        }
    }

    for(int i = 0; i<N; i++) {
        if(color[i]!=0) continue;
        for(int j : adj[i]) {
            if(color[j]!=0) continue;
            if(i > j) continue;
            // logical condition: both have blockcount == 2;
            // assert(countblocked(i)==2 && countblocked(j)==2);
            // blockcount = 1, 0 would be picked up earlier by solve1
            // blockcount = 3 is not possible if earlier arrays constructed right
            int bi = -2, bj = -1;
            for(int a = 0; a<3; a++) {
                if(blocked[3*i+a]) bi = a;
                if(blocked[3*j+a]) bj = a;
            }

            if(bi == -2 || bj == -1) return false;

            if(bi == bj) { // same blocked, either one we pick implies another
                int c2 = (bi+1)%3;
                int c3 = (bi+2)%3;
                sadj[3*i+c2].push_back(3*j+c3);
                sadj[3*i+c3].push_back(3*j+c2);
                sadj[3*j+c2].push_back(3*i+c3);
                sadj[3*j+c3].push_back(3*i+c2);
                radj[3*i+c2].push_back(3*j+c3);
                radj[3*i+c3].push_back(3*j+c2);
                radj[3*j+c2].push_back(3*i+c3);
                radj[3*j+c3].push_back(3*i+c2);

            }
            else { // different blocked, if i is colored with shared, then j is colored with blocked i
                int c = 0;
                for(; c<3; c++) {
                    if(c==bi || c == bj) continue;
                    break;
                }
                sadj[3*i+c].push_back(3*j+bi);
                sadj[3*j+c].push_back(3*i+bj);
                radj[3*j+bi].push_back(3*i+c);
                radj[3*i+bj].push_back(3*j+c);
            }
        }
    }

    // printsadj();
    // cout << endl;
    // printradj();

    // clear 2sat arrays
    // for each edge a-b:
    // 2 cases:
    //     a and b both can't be color 1
    //         a2 -> b3
    //         b2 -> a3
    //         b3 -> a2
    //         a3 -> b2
    //     a can't be 1, b can't be 2
    //         a3 -> b1
    //         b3 -> a2
    return true;
}

bool check(vector<int>& poss) { // poss[i] = i-th neighbor of ceo
    // in = poss[in[i]] is the i-th manager of current ceo
    int m = 1<<in.size(); // in.size() is always greater than 0
    for(int i = 0; i<m; i++) { // corresponds to different coloring of managers
        for(int j = 0; j<3*N; j++) blocked[j] = false;
        for(int j = 0; j<N; j++) color[j] = 0;
        color[CEO] = 1;
        blocked[3*CEO+1] = true;
        blocked[3*CEO+2] = true;
        for(int a : adj[CEO]) {
            blocked[3*a] = true;
        }
        int num = 1;
        for(int j = 0; j<in.size(); j++) {
            if ((num & i) == 0) {
                color[poss[in[j]]] = 2;
                blocked[3 * poss[in[j]]] = true;
                blocked[3 * poss[in[j]] + 2] = true;
            } else {
                color[poss[in[j]]] = 3;
                blocked[3 * poss[in[j]]] = true;
                blocked[3 * poss[in[j]] + 1] = true;
            }
            // do blocked array stuff

            for (int a: adj[poss[in[j]]]) {
                blocked[3 * a + color[poss[in[j]]] - 1] = true;
            }
            num *= 2;
        }
        if(!generate()) continue; // if this does not make a valid SCC (or if solve1 fails) try next

        if(SCC()) return true;

    }
    // clear scc arrays
    // clear colors (except for managers, can be done with bool array)
    // run DFS scc algorithm
    // topologically sort SCCs in reverse order
    //     if each node in SCC is undecided OR true, AND all child SCCs are true
    //         mark SCC as true, validate all literals inside SCC
    //     otherwise return false
    // if we can mark every node with some color (the cases where some are not markable will be because the SCCs they imply are not true)
    //     return true, which will go all the way out of the recursion and print out the colors that we decide on
    color[CEO] = 0;
    return false;
}

bool rec(int num, vector<int>& poss) {
    // for(int a : in) cout << poss[a] << " ";
    // cout << ": " << viscount << endl;
    if(viscount==N) {
        // cout << "yes" << endl;
        return true;
    }
    if(num==8) return false;
    int i = 0;
    if(!in.empty()) {
        i = in.back()+1;
    }
    for( ; i<poss.size(); i++) {
        if(visited[poss[i]]==0) viscount++; // visit itself
        visited[poss[i]]++;
        for(int a : adj[poss[i]]) { // visit neighbors
            if(visited[a]==0) viscount++;
            visited[a]++;
        }
        in.push_back(i);
        if(rec(num+1, poss)) return true;
        in.pop_back();
        for(int a : adj[poss[i]]) {
            visited[a]--;
            if(visited[a]==0) viscount--;
        }
        visited[poss[i]]--;
        if(visited[poss[i]]==0) viscount--;
    }
    return false;
}

bool cover(int ceo) {
    // choose some group of up to 8 managers that covers all nodes (use queue? recursion?)
    // if subset is found,
    //     try all ways to color the managers,
    //          for each color mark each node with colors that it cannot be (use larger "possible" array)
    //          then call a generate function to make the graph, then a check function to see if it is satisfiable (scc alg)
    //          if works, returns true and leaves a vector with the SCCs
    CEO = ceo;
    viscount = 0;
    in.clear();
    for(int i = 0; i<N; i++) visited[i] = 0;
    if(rec(0, adj[ceo])) return true;
    return false;
}

bool within(int ceo) {
    vector<int> dist(N, 2*N);
    queue<int> q;
    q.push(ceo);
    dist[ceo] = 0;
    while(!q.empty()) {
        int n = q.front();
        q.pop();
        if(dist[n]>2) return false;
        for(int a : adj[n]) {
            if(dist[a]==2*N) {
                dist[a] = dist[n]+1;
                if(dist[a]>2) return false;
                q.push(a);
            }
        }
    }
    return true;
}

bool find() {
    // iterate through all ceos
    //    check if degree <= 15
    //    check if distance <=2 from all other nodes
    // if yes, call cover(n)
    //
    for(int i = 0; i<N; i++) {
        if(adj[i].size()>15 || adj[i].empty()) continue;
        if(within(i)) {
            // cout << "possible: " << i << endl;
            if(cover(i)) { // if managers cover graph
                // check if some coloring works
                // if doesn't work for these managers, no set of managers will work.
                return check(adj[i]);
            }
        }
    }
    return false;
}

int main() {

    cin >> N >> M;

    for(int i = 0; i<M; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    if(!find()) cout << "Impossible" << endl;
    else {
        for(int i = 0; i<N; i++) cout << color[i] << " ";
        cout << endl;
        // validate answer
        for(int i = 0; i<N; i++) {
            if(color[i]==0) cout << "what" << endl;
            for(int a : adj[i]) {
                if(color[i]==color[a]) cout << "brick" << endl;
            }
        }
    }

}
