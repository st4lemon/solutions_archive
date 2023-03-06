// UCSB ICPC Qualifier 2023: Prime Time (NCPC 2011 I)
#include <bits/stdc++.h>

#define MAXN 10010

using namespace std;

unordered_set<int> primes;
int N;
vector<int> dp[MAXN];
vector<int> primecase = {1, 0, 0};

void rotate(vector<int>& v) {
    int temp = v[0];
    v[0] = v[2];
    v[2] = v[1];
    v[1] = temp;
}

void copy(vector<int> v, int row) {
    dp[row][0] = v[0];
    dp[row][1] = v[1];
    dp[row][2] = v[2];
}

string indent = "";

vector<int> rec(int n) {
    if(n==1) return dp[n];
    if(dp[n][0]!=0) return dp[n];
    // cout << indent << n << endl;
    // indent += "   ";
    // case 1: n is prime
    if(primes.find(n) != primes.end()) {
        copy(primecase, n);
//        indent.erase(0, 3);
//        cout << indent << n << ": " << dp[n][0] << " " << dp[n][1] << " " << dp[n][2] << endl;
        return primecase;
    }
    // case 2: try adding 1
    vector<int> v = rec(n+1);
    rotate(v);
    if(v[0] == 0 || v[0] > n+1) v[0] = n+1;

    int next = n+1;
    // case 3: try primes
    for(auto it = primes.begin(); it!=primes.end(); it++) {
        int val = *it;
        if(n%val!=0) continue;
        int num = n/val;
        vector<int> res = rec(num);
        rotate(res);
        if(res[0]==0 || res[0] > num) res[0] = num;
        if(res[0] < v[0]) {
            v = res;
            next = num;
        }
        else if(res[0]==v[0] && num < next) {
            v = res;
            next = num;
        }
    }
    copy(v, n);
//    indent.erase(0, 3);
//    cout << indent << n << ": " << dp[n][0] << " " << dp[n][1] << " " << dp[n][2] << endl;
    return dp[n];
}

int main() {

    cin >> N;

    primes.insert(2);
    for(int i = 3; i<=10007; i+=2) {
        bool works = true;
        for(auto it = primes.begin(); it != primes.end(); it++) {
            int v = *it;
            if(i%v == 0) {
                works = false;
                break;
            }
        }
        if(works) primes.insert(i);
    }

    for(int i = 0; i<=10007; i++) {
        for(int j = 0; j<3; j++) {
            dp[i].push_back(0);
        }
    }

/*
    for(int i = 1; i<20; i++) {
        cout << i << ": " << dp[i][0] << " " << dp[i][1] << " " << dp[i][2] << endl;
    }
*/

    int O = 0;
    int E = 0;
    int I = 0;
    // order is O > E > I > O

    for(int i = 0; i<N; i++) {
        char c;
        int start;
        cin >> c >> start;
        vector<int> ans = rec(start);
        for(int i = 0; i<3; i++) {
            if(ans[i]==0) ans[i] = start;
        }
        if(c=='O') {
            O += ans[0];
            E += ans[1];
            I += ans[2];
        }
        else if(c=='E') {
            E += ans[0];
            I += ans[1];
            O += ans[2];
        }
        else {
            I += ans[0];
            O += ans[1];
            E += ans[2];
        }
    }

    cout << O << " " << E << " " << I << endl;

}
