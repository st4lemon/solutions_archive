#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll N, M, K, pa, pb;

ll cords[200005];
ll ta[100005]; // how much alice wants
ll tb[100005]; // how much bob wants

vector<array<ll, 4>> plates;
ll ans = 0;

bool check(ll L) {
    // cout << "check " << L << endl;
    ans = 0;
    vector<ll> ar(M, 0), br(M, 0), tr(M, 0);
    for(auto& [cost, amt, type, loc] : plates) {
        ll need = min(amt, ta[type] + tb[type] - tr[type]); // total needed - total taken
        bool ina = ((pa - loc + N) % N <= L);
        bool inb = ((pb - loc + N) % N <= L);
        if(!inb && !ina) {
            continue;
        }
        else if(ina && !inb) {
            need = min(need, ta[type] - ar[type]);
            ar[type] += need;
        }
        else if(inb && !ina) {
            need = min(need, tb[type] - br[type]);
            br[type] += need;
        }
        tr[type] += need;
        // cout << cost << " " << amt << " " << type << " " << loc << " " << need << endl;
        // cout << ina << " " << inb << endl;
        ans += need * cost;
    }
    // for(int i = 0; i<M; i++) cout << ar[i] << " " << br[i] << " " << tr[i] << endl; 
    for(int i = 0; i<M; i++) {
        if(tr[i] < ta[i] + tb[i]) return false;
    }
    return true;
}

int main() {

    cin >> N >> M >> K >> pa >> pb;
    pa--;
    pb--;

    for(int i = 0; i<M; i++) {
        cin >> ta[i];
    }
    for(int i = 0; i<M; i++) cin >> tb[i];

    for(int i = 0; i<K; i++) {
        ll s, t, x, c;
        cin >> s >> t >> x >> c;
        s--;
        t--;
        plates.push_back({c, x, t, s}); // cost, amt, type, starting loc
    }
    // for(int i = 0; i<M; i++) cout << ta[i] << " " << tb[i] << endl;

    sort(plates.begin(), plates.end());

    ll low = 0, high = N;
    while(low < high) {
        ll m = (low + high) / 2;
        if(check(m)) {
            high = m;
        }
        else {
            low = m+1;
        }
    }

    if(low == N) {
        cout << "impossible" << endl;
        return 0;
    }

    check(low);
    cout << low << " " << ans << endl;

}