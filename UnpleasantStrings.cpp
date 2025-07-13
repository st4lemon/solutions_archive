// https://codeforces.com/contest/2104/problem/E 

#include <bits/stdc++.h>
using namespace std;

int trans[1000005][26] = {0};
int best[1000005] = {0};
int steps[1000005] = {0};
int N, K, Q;
int last[26];

int compute(int num) {
    // cout << "    " << num << endl;
    if(num >= N+1) return 0;
    if(steps[num] != -1) return steps[num];
    steps[num] = compute(best[num]+1) + 1;
    return steps[num];
}

void solve() {

    string str;
    cin >> str;
    int S = str.length();

    // compute earliest matching subsequence
    int loc = 0;
    for(int i = 0; i<S; i++) {
        int ind = (int)(str[i] - 'a');
        loc = trans[loc][ind]+1;
        if(loc >= N+1)  {
            break;
        }
    }

    // "best" array generates edges of worst character possibilities
    cout << compute(loc) << endl;

}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;

    for(int i = 0; i<K; i++) {
        last[i] = N;
    }

    for(int i = 0; i<=N+2; i++) {
        steps[i] = -1;
    }

    string s;
    cin >> s;
    for(int i = N-1; i>=0; i--) {
        int ind = (int)(s[i] - 'a');
        for(int j = 0; j<K; j++) {
            trans[i+1][j] = last[j];
            best[i+1] = max(best[i+1], last[j]);
        }
        last[ind] = i;
    }
    for(int i = 0; i<K; i++) {
        trans[0][i] = last[i];
        best[0] = max(best[0], last[i]);
    }


    cin >> Q;
    for(int i = 0; i<Q; i++) {
        solve();
    }

}
