// 2023 Socal ICPC Regional: Distinct Parity Excess (Problem 8)
#include <bits/stdc++.h>
using namespace std;

#define MAX 10000000

int cnt[MAX+1] = {0};
int oddpref[MAX+1] = {0};
int evenpref[MAX+1] = {0};

int main() {


    // PRECOMPUTE TABLE
    for(int i = 2; i<=MAX; i++) {
        if(cnt[i]!=0) continue;
        for(int j = i; j<=MAX; j+=i) {
            cnt[j]++;
        }
    }

    for(int i = 2; i<=MAX; i++) {
        oddpref[i] = oddpref[i-1];
        evenpref[i] = evenpref[i-1];
        if(cnt[i]%2==0) evenpref[i]++;
        else oddpref[i]++;
    }

    int n, m;
    while(cin >> n) {
        cin >> m;
        int odd = oddpref[m]-oddpref[n-1];
        int even = evenpref[m]-evenpref[n-1];
        cout << (even-odd) << endl;
    }

}