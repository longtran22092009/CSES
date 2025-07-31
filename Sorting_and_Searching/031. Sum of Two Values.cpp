#include <bits/stdc++.h>
using namespace std;
//====== BITWISE ======//
#define MASK(i) (1LL << (i))
#define BIT(x, i) (1LL & ((x) >> (i)))
#define ON(x, i) ((x) | MASK(i))
#define OFF(x, i) ((x) & ~MASK(i))
#define LASTBIT(mask) ((mask) & -(mask))
#define SUBMASK(sub, mask) for (int sub = (mask); sub >= 1; sub = (sub - 1) & (mask))
//====== OTHER ======//
#define fi first
#define se second
#define ll long long
#define endl '\n'
#define sz(x) (int)size(x)
#define all(x) begin(x), end(x)
#define mod(x, k) ((((x) % (k)) + (k)) % (k))
#define compress(c) sort(all(c)); c.erase(unique(all(c)), c.end());
#define Longgggg ios_base::sync_with_stdio(0); cin.tie(0);
#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define FORD(i, a, b) for (int i = (a); i >= (b); i--)
//====== FILE ======//
#define IN "A.in"
#define OUT "A.out"
#define DEBUG "debug.out"
//==================//

const int INF = (int) 1e9+5;
const ll LINF = (ll) 1e18;
const ll MOD = (ll) 1e9+7;
const int mxN = 100005;

void solve() {
    /// Using map
    // int n, tgt; cin >> n >> tgt;
    // vector <int> a(n);
    // map <int, int> f;
    // FOR(i, 0, n-1) {
    //     cin >> a[i];
    //     f[a[i]]++;
    // }
    // for (auto &x : a) {
    //     int need = tgt - x;
    //     --f[x];
    //     if (f[need]) {
    //         int id1 = find(all(a), x) - a.begin();
    //         int id2 = find(a.begin()+id1+1, a.end(), need) - a.begin();
    //         cout << id1+1 << " " << id2+1 << endl;
    //         return;
    //     }
    //     ++f[x];
    // }
    // cout << "IMPOSSIBLE\n";

    /// Using two pointer
    int n, tgt; cin >> n >> tgt;

    vector <pair <int, int>> a(n);
    FOR(i, 0, n-1) {
        int x; cin >> x;
        a[i] = {x, i+1};
    }
    sort(all(a));

    int l = 0, r = n-1;
    while (l < r) {
        int sum = a[l].fi + a[r].fi;
        if (sum == tgt) {
            cout << a[l].se << " " << a[r].se << endl;
            return;
        }
        else if (sum > tgt) --r;
        else ++l;
    }

    cout << "IMPOSSIBLE\n";
}

signed main() {
    if (fopen(IN, "r")) {
        freopen(IN, "r", stdin);
        freopen(OUT, "w", stdout);
        freopen(DEBUG, "w", stderr);
    }
    Longgggg

    ll t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}
