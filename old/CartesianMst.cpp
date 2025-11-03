/*

https://codeforces.com/gym/103098/problem/C
2020-2021 Winter Petrozavodsk Camp, UPC Contest #C: Cartesian MST

Problem: Let G and H be two weighted undirected graphs. Define the cartesian product of the two graphs, G~H, as the graph whose vertex set is the cartesian set product of the vertex sets of the two graphs, in which there is an edge between vertices (u1, v1) and (u2, v2) if and only if:
- v1 = v2 and there is an edge (u1, u2) in G; with ((u1, v1), (u2, v2)) taking the same weight as (u1, u2), or
- u1 = u2 and there is an edge (v1, v2) in H; with ((u1, v1), (u2, v2)) taking the same weight as (v1, v2)

You are given two connected graphs G and H. Compute the total weight of the minimum spanning tree of G~H.


Solution:
We note two things here:
 - If we order all the edges in G~H by their weight, then the edges in G appear in the same order and the edges of H appear in the same order.
 - There exists an optimal ordering such that all edges corresponding to the same original edge appear next to each other.

If we run Kruskal's algorithm on G~H, it would take far too long because of the number of edges there are, but as a result of the first and second property, we can run Kruskal's algorithm on G and H individually, and whenever we reach an edge of G or H that can be added to their respective minimum spanning trees, we can add multiple edges of the same type to the MST of G~H. This simply performs Kruskal's algorithm on the optimal ordering of edges described above, but with far less manual steps.

However, it's not as simple as adding N edges instead of 1 edge every time we process an edge; for example, as we connect edges from graph G, there are less components that we need to connect using edges from graph H. A simple example is below:

      u1  u2  u3  u4           u1  u2  u3  u4  
 v1   O   O - O   O       v1   O   O - O   O      

 v2   O   O - O   O       v2   O   O - O   O      
                               |   |       |     ==> note that we only need to add 3 (v2-v3) edges
 v3   O   O - O   O       v3   O   O - O   O           because (u2-u3) is already connected.

 v4   O   O - O   O       v4   O   O - O   O      

So, when we add edges from H, we add (N - # edges added from G) edges, and vice versa. 

*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<pll, pll> edge; // <<weight, graph>, <from, to>>

int group(int val, vector<int>& par);

void join(int a, int b, vector<int>& par, vector<int>& siz);

int main() {

    int n1, m1, n2, m2;
    cin >> n1 >> m1 >> n2 >> m2;

    vector<edge> edges;
    for(int i = 0; i<m1; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        a;
        b;
        edges.emplace_back(make_pair(d, 1), make_pair(a, b));
    }

    for(int i = 0; i<m2; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        a;
        b;
        edges.emplace_back(make_pair(d, 2), make_pair(a, b));
    }

    vector<int> par1(n1);
    vector<int> par2(n2);
    vector<int> siz1(n1, 1);
    vector<int> siz2(n2, 1);

    for(int i = 0; i<n1; i++) {
        par1[i] = i;
    }

    for(int i = 0; i<n2; i++) {
        par2[i] = i;
    }

    sort(edges.begin(), edges.end());

    int cnt1 = 0;
    int cnt2 = 0;
    ll ans = 0;
    for( edge& e : edges ) {
        ll w = e.first.first;
        ll g = e.first.second;
        ll x = e.second.first;
        ll y = e.second.second;

        if( g == 1 ) {
            if( group(x, par1) == group(y, par1) ) {
                continue;
            }
            ans += (n2-cnt2)*w;
            join(x, y, par1, siz1);
            cnt1++;
        } 
        else {
            if( group(x, par2) == group(y, par2) ) {
                continue;
            }
            ans += (n1-cnt1)*w;
            join(x, y, par2, siz2);
            cnt2++;
        }
    }

    cout << ans << endl;

}

int group(int val, vector<int>& par) {
    if(par[val] == val) return val;
    par[val] = group(par[val], par);
    return par[val];
}

void join(int a, int b, vector<int>& par, vector<int>& siz) {
    int pa = group(a, par);
    int pb = group(b, par);
    if(siz[pa] > siz[pb]) {
        siz[pa] += siz[pb];
        par[pb] = pa;
    }
    else {
        siz[pb] += siz[pa];
        par[pa] = pb;
    }
}
