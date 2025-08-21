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
#define sz(x) (int)x.size()
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
const int mxN = (int) 2e5+5;

struct Fenwick {
    int n;
    vector <ll> bit;

    Fenwick(int _n) {
        n = _n;
        bit.assign(n+1, 0LL);
    }

    void update(int idx, ll val) {
        for (; idx <= n; idx += LASTBIT(idx)) bit[idx] += val;
    }

    ll query(int idx) {
        ll sum = 0;
        for (; idx > 0; idx -= LASTBIT(idx)) sum += bit[idx];
        return sum;
    }

    ll range_query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l-1);
    }
};

int n, Q, timeDfs = 0; 
vector <int> adj[mxN], tin(mxN, 0), tout(mxN, 0);
vector <ll> a(mxN);

void dfs(int u, int pre) {
    tin[u] = ++timeDfs;
    for (auto &v : adj[u]) 
        if (v != pre) dfs(v, u);
    tout[u] = timeDfs;
}

void solve() {
    cin >> n >> Q;
    FOR(i, 1, n) cin >> a[i];

    FOR(i, 1, n-1) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);
    Fenwick bit(n);
    FOR(i, 1, n) bit.update(tin[i], a[i]);

    while (Q--) {
        int op; cin >> op;

        if (op == 1) {
            int p; ll v; cin >> p >> v;
            bit.update(tin[p], v - a[p]);
            a[p] = v;
        }
        else {
            int u; cin >> u;
            cout << bit.range_query(tin[u], tout[u])<< endl;
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
