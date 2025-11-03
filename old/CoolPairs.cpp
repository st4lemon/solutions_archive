// 300iq Contest 1: Cool Pairs
// https://codeforces.com/gym/102268/problem/C 
#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; t = 1;
    while (t--) {
        int n; cin >> n;
        ll k; cin >> k;
        vector<int> p(n), q(n);
        for (int& x : p) cin >> x;
        for (int& x : q) cin >> x;

        ll cnt = 0;
        vector<int> ans1(n), ans2(n);

        for (int i = 0; i < n; i++) {
            ans2[q[i] - 1] = -n + i;
        }

        for (int i = 0; i < n; i++) {
            // cout << i << endl;

            int pos = p[i] - 1;
            int smaller = n - 1 - pos;

            // cout << cnt << endl;

            if (cnt >= k) {
                ans1[pos] = n;
            } else if (cnt + smaller <= k) {
                // cout << "xd1" << endl;
                // cout << "setting to zero: " << pos[i + 1] << endl;
                ans1[pos] = 0;
                cnt += smaller;
                // cout << "values: " << values[i] << endl;
            } else { // query and binary search
                // cout << "xd2" << endl;
                // cout << pos[i + 1] << endl;
                vector<int> arr;
                for (int j = 0; j < smaller; j++) {
                    arr.push_back(ans2[n - 1 - j]);
                }
                sort(arr.begin(), arr.end());
                // for (int& x : arr) cout << x << " ";
                // cout << endl;
                ll diff = k - cnt;
                assert(diff < arr.size());
                // cout << "diff: " << diff << endl;
                ans1[pos] = -arr[diff];
                cnt = k;
            } 
        }

        if (cnt != k) {
            cout << "No\n";
        } else {
            cout << "Yes\n";
    
            for (int& x : ans1) cout << x << " ";
            cout << endl;
            for (int& x : ans2) cout << x << " " ;
            cout << endl;
        }


    }
    return 0;
}
