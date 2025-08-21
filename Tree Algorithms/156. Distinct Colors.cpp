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

int n;
vector <int> adj[mxN], color(mxN), ans(mxN);
vector <set <int>> tree(mxN);

void dfs(int u, int pre) {
    int big = -1;
    for (auto &v : adj[u]) {
        if (v == pre) continue;
        dfs(v, u);
        // Find the biggest set of color
        if (big == -1 || sz(tree[big]) < sz(tree[v])) big = v;
    }

    if (big != -1) swap(tree[u], tree[big]);
    tree[u].insert(color[u]);
    for (auto &v : adj[u]) {
        if (v == pre || v == big) continue;
        tree[u].insert(all(tree[v]));
    }

    ans[u] = sz(tree[u]);
}

void solve() {
    cin >> n;

    FOR(i, 1, n) cin >> color[i];

    FOR(i, 1, n-1) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);
    FOR(i, 1, n) cout << ans[i] << " ";
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
