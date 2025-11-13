#include <bits/stdc++.h>
using namespace std;

int def[3][3] = {
    {0, 3, 2},
    {3, 4, 1},
    {2, 1, 4}
};

int main() {
    
    bool corner;
    int nx, ny, kx, ky, cx, cy;
    cin >> nx >> ny >> kx >> ky >> cx >> cy;
    corner = (cx == 0 || cx == nx - 1) && (cy == 0 || cy == ny - 1);
    corner |= (kx == 0 || kx == nx - 1) && (ky == 0 || ky == ny - 1);
    kx -= cx;
    ky -= cy;
    cx = 0;
    cy = 0;
    kx = abs(kx);
    ky = abs(ky);
    if(kx < ky) {
        swap(kx, ky);
    }
    
    // cout << cx << " " << cy << " " << kx << " " << ky << endl;
    if(ky == 1 && kx == 1) {
        if(corner) {
            cout << 4 << endl;
        }
        else {
            cout << 2 << endl;
        }
        return 0;
    }
    
    if(ky <= 2 && kx <= 2) {
        cout << def[kx][ky] << endl;
        return 0;
    }
    
    if(ky <= (kx+1)/2) {
        int low = (kx+1)/2;
        int par = (kx+ky)%2;
        if(par != low % 2) {
            low += 1;
        }
        cout << low << endl;
    }
    else {
        int low = (kx + ky + 1)/3;
        int par = (kx+ky)%2;
        if(par != low % 2) {
            low += 1;
        }
        cout << low << endl;
    }
    
}
