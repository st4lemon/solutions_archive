// UCSB ICPC Qualifier 2023: Enemy Division (NCPC 2011 J)
#include <bits/stdc++.h>

using namespace std;

#define MAXN 100010

int group[MAXN] = {0};
int one[MAXN] = {0};
int two[MAXN] = {0};
int N, M;

vector<int> adj[MAXN];

int main() {

    cin >> N >> M;

    for(int i = 0; i<M; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for(int i = 1; i<=N; i++) {
        if(one[i]>1) {
            group[i] = 2;
            for(int a : adj[i]) {
                two[a]++;
            }
        }
        else {
            group[i] = 1;
            for(int a : adj[i]) {
                one[a]++;
            }
        }
    }

    queue<int> q;
    for(int i = 0; i<N; i++) {
        if(group[i]==1 && one[i]>1) q.push(i);
        else if(group[i]==2 && two[i]>1) q.push(i);
    }

    while(!q.empty()) {
        int n = q.front(); q.pop();
        // check to see if you still need to swap color
        if(group[n]==1 && one[n]>1) {
            group[n] = 2;
            for(int a : adj[n]) {
                two[a]++;
                one[a]--;
                if(group[a]==1 && one[a]>1 || group[a]==2 && two[a]>1) q.push(a);
            }
        }
        else if(group[n]==2 && two[n]>1) { // if it is 2 and has two neighbors of 2
            group[n] = 1;
            for(int a : adj[n]) {
                one[a]++;
                two[a]--;
                if(group[a]==1 && one[a]>1 || group[a]==2 && two[a]>1) q.push(a);
            }
        }
    }

    multiset<int> first;
    multiset<int> second;
    for(int i = 1; i<=N; i++) {
        if(group[i]==1) first.insert(i);
        else second.insert(i);
    }

    // conflict detection


    if(second.size()<=0) {
        cout << 1 << endl;
        for(int a : first) {
            cout << a << " ";
        }
        cout << endl;
    }
    else {
        cout << 2 << endl;
        for(int a : first) {
            cout << a << " ";
        }
        cout << endl;
        for(int a : second) {
            cout << a << " ";
        }
        cout << endl;
    }

}