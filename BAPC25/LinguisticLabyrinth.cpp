//
#include <bits/stdc++.h>
using namespace std;


typedef long long ll;

array<int, 3> get(int x, int y, int z) {
    if(x < 0) {
        x *= -1;
        y *= -1;
        z *= -1;
    }
    int xa = abs(x), ya = abs(y), za = abs(z);
    int g = max(xa, max(ya, za));
    if(x != 0) g = gcd(g, xa);
    if(y != 0) g = gcd(g, ya);
    if(z != 0) g = gcd(g, za);
    return {x/g, y/g, z/g};
}

int N;

string grid[22][22];
int nind[22][43][43] = {{{0}}};

bool inbounds(int& x, int& y, int& z, int& a, int& b, int& c, int& mx, int& mn) {
    int u = (a+x)*x + (b+y)*y + (c+z)*z;
    int v = (a-x)*x + (b-y)*y + (c-z)*z;
    if((u > mx || u < mn) && (v > mx || v < mn)) return false; // if +xyz and -xyz are out of bounds, return false.
    return true;
}

int main() {

    /*
     * solution:
     * find all possible gcd'ed normal vectors
     * for each one, compute the level that each B and C is at. This can be stored as a count.
     * then for each AP pair, find their normal vector and find all the Bs that are at the correct level.
     */

    cin >> N;

    int half = 3*N*N;
    // map<char, vector<array<int, 3>>> mp;

    char _;
    for(int i = 0; i<N; i++) {
        cin >> _;
        for(int j = 0; j<N; j++) {
            cin >> grid[i][j];
        }
    }

    set<array<int, 3>> norms;
    for(int xa = 0; xa < N; xa++) {
        for(int ya = 0; ya < N; ya++) {
            for(int za = 0; za < N; za++) {
                if(grid[xa][ya][za] != 'A') {
                    continue;
                }
                for(int xp = 0; xp < N; xp++) {
                    for(int yp = 0; yp < N; yp++) {
                        for(int zp = 0; zp < N; zp++) {
                            if(grid[xp][yp][zp] != 'P') {
                                continue;
                            }
                            norms.insert(get(xp-xa, yp-ya, zp-za));
                        }
                    }
                }
            }
        }
    }


    vector<array<int, 3>> norm(norms.begin(), norms.end());

    for(int i = 0; i<(int)norm.size(); i++) {
        nind[norm[i][0]][norm[i][1]+N-1][norm[i][2]+N-1] = i;
        // cout << "norm " << i << ": " << norm[i][0] << " " << norm[i][1] << " " << norm[i][2] << endl;
    }
    vector<vector<int>> cntB(norm.size(), vector<int>(6*N*N, 0));
    vector<vector<int>> cntC(norm.size(), vector<int>(6*N*N, 0));

    for(int xa = 0; xa < N; xa++) {
        for(int ya = 0; ya < N; ya++) {
            for(int za = 0; za < N; za++) {
                if(grid[xa][ya][za] != 'A') {
                    continue;
                }
                for(int xp = 0; xp < N; xp++) {
                    for(int yp = 0; yp < N; yp++) {
                        for(int zp = 0; zp < N; zp++) {
                            if(grid[xp][yp][zp] != 'P') {
                                continue;
                            }
                            array<int, 3> ap = get(xp-xa, yp-ya, zp-za);
                            cntB[nind[ap[0]][ap[1]+N-1][ap[2]+N-1]][ap[0] * xa + ap[1] * ya + ap[2] * za + half] = 1;
                            cntC[nind[ap[0]][ap[1]+N-1][ap[2]+N-1]][ap[0] * xp + ap[1] * yp + ap[2] * zp + half] = 1;
                        }
                    }
                }
            }
        }
    }

    for(int i = 0; i<norm.size(); i++) {
        // find levels of every norm
        auto& [x, y, z] = norm[i];
        int mx = max(N*x, 0) + max(N*y, 0) + max(N*z, 0);
        int mn = min(N*x, 0) + min(N*y, 0) + min(N*z, 0);
        // cout << "norm: " << x << " " << y << " " << z << endl;
        for(int a = 0; a < N; a++) {
            for(int b = 0; b < N; b++) {
                for(int c = 0; c < N; c++) {
                    if(!inbounds(x, y, z, a, b, c, mx, mn)) continue;
                    // cout << a << " " << b << " " << c << endl;
                    int dot = a*x + b*y + c*z + half;
                    if(grid[a][b][c] == 'B') {
                        if(cntB[i][dot] == 0) continue;
                        cntB[i][dot]++;
                    }
                    else if(grid[a][b][c] == 'C') {
                        if(cntC[i][dot] == 0) continue;
                        cntC[i][dot]++;
                    }
                }
            }
        }
    }

    // find all APs
    ll ans = 0;
    for(int xa = 0; xa < N; xa++) {
        for(int ya = 0; ya < N; ya++) {
            for(int za = 0; za < N; za++) {
                if(grid[xa][ya][za] != 'A') {
                    continue;
                }
                for(int xp = 0; xp < N; xp++) {
                    for(int yp = 0; yp < N; yp++) {
                        for(int zp = 0; zp < N; zp++) {
                            if(grid[xp][yp][zp] != 'P') {
                                continue;
                            }
                            array<int, 3> ap = get(xp-xa, yp-ya, zp-za);
                            if(cntB[nind[ap[0]][ap[1]+N-1][ap[2]+N-1]][ap[0] * xa + ap[1] * ya + ap[2] * za + half] <= 1) {
                                continue;
                            }
                            if(cntC[nind[ap[0]][ap[1]+N-1][ap[2]+N-1]][ap[0] * xp + ap[1] * yp + ap[2] * zp + half] <= 1) {
                                continue;
                            }
                            ll curr = cntB[nind[ap[0]][ap[1]+N-1][ap[2]+N-1]][ap[0] * xa + ap[1] * ya + ap[2] * za + half] - 1;
                            curr *= cntC[nind[ap[0]][ap[1]+N-1][ap[2]+N-1]][ap[0] * xp + ap[1] * yp + ap[2] * zp + half] - 1;
                            ans += curr;
                        }
                    }
                }
            }
        }
    }
    cout << ans << endl;

}
