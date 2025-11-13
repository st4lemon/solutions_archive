//
#include <vector>
#include <iostream>
using namespace std;

#define len 2000000

typedef long long ll;

int N;
ll fls[35] = {0};
ll waits[35] = {0};

ll test(vector<ll>& phase) {
    ll pos = 0;
    ll time = 0;

    for(int i = 0; i<N; i++) {
        // choose elevator to take to floor i
        ll targ = pos;
        if(fls[i] < pos) targ = len - targ;
        int elev = 0;
        for(int j = 1; j<=3; j++) {
            ll curr = (phase[elev] + time) % (len);
            ll next = (phase[j] + time) % (len);
            if((targ - curr + len) % len > (targ - next + len) % len) {
                elev = j;
            }
        }
        time += (targ - (phase[elev] + time) % len + len) % len + abs(pos - fls[i]) + waits[i];
        // cout << i << " " << time << " " << elev << endl;
        pos = fls[i];

    }

    return time;
}

ll settime(vector<int>& par) {
    ll ret = 1e18;
    vector<ll> phase(4, 0);
    vector<int> meet(4, 0);
    for(meet[1] = 0; meet[1]<N; meet[1]++) {
        for(meet[2] = 0; meet[2]<N; meet[2]++) {;
            for(meet[3] = 0; meet[3]<N; meet[3]++) {
                for(int mask = 0; mask < 8; mask++) {
                    for(int n = 1; n<=3; n++) {
                        // n gets on when par[n] has passed wait[i] time.
                        ll t = fls[meet[n]];
                        if(meet[n] > 0 && fls[meet[n]-1] > fls[meet[n]]) t = len - t;
                        t += waits[meet[n]];
                        t %= len;
                        ll l = fls[meet[n]];
                        if((mask & (1<<(n-1))) > 0) l = (len - l) % len;
                        phase[n] = (phase[par[n]] + l - t + len) % len;
                    }
    
                
                    ret = min(ret, test(phase));
                }
            }
        }
    }
    return ret;
}

int main() {

    /*
     * There are 3 possible trees with 4 nodes.
     * Root the tree at 1, which starts at level 0.
     *   Try all n^3 possible choices for where an elevator meets. This sets the starting point for all elevators.
     *   Suppose 1 meets 2 at a certain floor. We know the phase of 1 and the wait time at that floor, so we can exactly compute the phase of 2.
     *
     */

    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for(int i = 0; i<N; i++) cin >> fls[i];
    for(int i = 0; i<N; i++) cin >> waits[i];

    ll ans = 1e18;
    vector<int> par(4, 0);
    for(par[2] = 0; par[2] <= 1; par[2]++) {
        for(par[3] = 0; par[3] <= 2; par[3]++) {
            // cout << "par: " << par[1] << " " << par[2] << " " << par[3] << endl;
            ans = min(ans, settime(par));
        }
    }

    cout << ans << endl;


}