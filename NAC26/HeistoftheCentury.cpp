#include <bits/stdc++.h>
using namespace std;

int ans[500];

int main() {

    int N;
    cin >> N;

    // find which ones are 2n
    for(int i = 0; i<N; i++) {
        for(int j = 0; j<N; j++) {
            if(j == i) cout << 1 << " ";
            else cout << N << " ";
        }
        cout << endl;
        int val;
        cin >> val;
        if(val == 2*N-1) {
            // cout << "Here" << endl;
            ans[i] = 2*N;
        }
        if(val == 0) return 0;
    }

    // then get stuff
    for(int i = 0; i<N; i++) {
        // cout << i << ": " << ans[i] << endl;
        if(ans[i] == 2*N) continue;
        vector<int> query(N, N); // assign all N
        for(int j = 0; j<N; j++) { // if we know it's 2*N, set query to 2*N
            if(ans[j] == 2*N) query[j] = 2*N;
        }
        query[i] = 1; // set i to 1

        for(int j = 0; j<N; j++) {
            cout << query[j] << ' ';
        }
        cout << endl;
        int v1;
        cin >> v1; // v1 = distance from 1
        if(v1 == 0) return 0;

        query[i] = 2*N-1; // set i to 2*N-1

        for(int j = 0; j<N; j++) {
            cout << query[j] << ' ';
        }
        cout << endl;
        int v2;
        cin >> v2; // v2 = distance from 2*N-1
        if(v2 == 0) return 0;

        if(v1 > v2) {
            ans[i] = v1 + 1;
        }
        else {
            ans[i] = 2*N-1 - v2;
        }
        // cout << "set " << i << " to " << ans[i] << endl;

    }

    for(int i =0; i<N; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;

}