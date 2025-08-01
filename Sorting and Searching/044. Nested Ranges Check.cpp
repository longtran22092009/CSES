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
    int n; cin >> n;

    vector <array <int, 4>> events;
    vector <pair <int, int>> edges(n);
    FOR(i, 0, n-1) {
        int l, r; cin >> l >> r;
        edges[i] = {l, r};
        events.push_back({0, l, 0, i});
        events.push_back({1, r, -l, i});
    }
    sort(all(events));
    
    multiset <int> active, done; // l
    vector <bool> a(n, false), b(n, false);

    for (auto &e : events) {
        if (e[0] == 0) active.insert(e[1]);
        else {
            int id = e[3], lval = edges[id].fi;
            active.erase(active.find(lval));
            if (sz(active) && *active.begin() <= lval) b[id] = true;
            if (sz(done) && *done.rbegin() >= lval) a[id] = true;
            done.insert(lval);
        }
    }

    FOR(i, 0, n-1) cout << a[i] << " ";
    cout << endl;
    FOR(i, 0, n-1) cout << b[i] << " ";
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
