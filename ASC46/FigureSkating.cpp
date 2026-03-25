#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr ll mod = 998244353;

struct mat{
    ll arr[4][4] = {0};
};

mat operator*(mat& a, mat& b) {
    mat ret;
    for(int i = 0; i<4; i++) {
        for(int j = 0; j<4; j++) {
            for(int k = 0; k<4; k++) {
                ret.arr[i][j] += a.arr[i][k] * b.arr[k][j];
                ret.arr[i][j] %= mod;
            }
        }
    }
    return ret;
}

ll base[4][4] = {
    {1, 1, 0, 0},
    {1, 2, 0, 1},
    {1, 2, 1, 2},
    {0, 0, 1, 1},
};

ll id[4][4] = {
    {1, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
};

void printmat(mat& m) {
    for(int i = 0; i<4; i++) {
        for(int j = 0; j<4; j++) {
            cout << m.arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    
    freopen("figure.in", "r", stdin);
    freopen("figure.out", "w", stdout);

    vector<mat> mats;
    mats.emplace_back();
    for(int i = 0; i<4; i++) {
        for(int j = 0; j<4; j++) {
            mats.back().arr[i][j] = base[i][j];
        }
    }
    for(int i = 1; i<=30; i++) {
        mats.push_back(mats.back()*mats.back());
        // printmat(mats.back());
    }
    

    int N;
    cin >> N;
    while(N != 0) {
        mat tmp;
        for(int i = 0; i<4; i++) {
            for(int j = 0; j<4; j++) {
                tmp.arr[i][j] = id[i][j];
            }
        }  

        ll num = (1 << 30);
        // cout << N << " " << num << endl;
        for(int i = 30; i>=0; i--) {
            if(N & num) {
                tmp = tmp * mats[i];
                // cout << "N: " << N << " " << num << endl;
            }
            num >>= 1;
        }

        cout << tmp.arr[0][0] << endl;
        
        cin >> N;
    }

}