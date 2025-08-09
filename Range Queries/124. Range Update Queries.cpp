#include <bits/stdc++.h>
using namespace std;
//====== BITWISE ======//
#define MASK(i) (1LL << (i))
#define BIT(x, i) (((x) >> (i)) & 1)
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
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
//====== FILE ======//
#define IN "A.in"
#define OUT "A.out"
#define DEBUG "debug.out"
//==================//

const int INF = (int) 1e9+5;
const ll LINF = (ll) 1e18;
const ll MOD = (ll) 1e9+7;
const int mxN = 100005;

struct Fenwick {
    int n;
    vector <ll> bit;

    Fenwick(int _n) {
        n = _n;
        bit.assign(n+1, 0LL);
    }

    void update(int idx, int val) {
        for (; idx <= n; idx += LASTBIT(idx)) 
            bit[idx] += val;
    }

    void range_update(int l, int r, int val) {
        update(l, val);
        update(r+1, -val);
    }

    ll query(int idx) {
        ll val = 0;
        for (; idx > 0; idx -= LASTBIT(idx))
            val += bit[idx];
        return val;
    }
};

void solve() {
    int n, Q; cin >> n >> Q;

    vector <int> a(n);
    for (auto &x : a) cin >> x;

    Fenwick bit(n);
    while (Q--) {
        int op; cin >> op;
        if (op == 1) {
            int l, r, val; cin >> l >> r >> val;
            bit.range_update(l, r, val);
        }
        else {
            int k; cin >> k;
            cout << a[k-1] + bit.query(k) << endl;
        }
    }
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
