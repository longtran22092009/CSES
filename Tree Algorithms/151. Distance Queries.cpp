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

const int LOG = 31;
vector <int> adj[mxN], depth(mxN, 0);
int up[mxN][LOG];

void dfs(int u, int pre) {
    for (auto &v : adj[u]) {
        if (v == pre) continue;

        up[v][0] = u;
        depth[v] = depth[u] + 1;
        FOR(j, 1, LOG-1) 
            up[v][j] = up[up[v][j-1]][j-1];
        dfs(v, u);
    }
}

int LCA(int a, int b) {
    if (depth[a] != depth[b]) {
        if (depth[a] < depth[b]) swap(a, b);
        int k = depth[a] - depth[b];
        FORD(j, LOG-1, 0) if (BIT(k, j)) a = up[a][j];
    }
    if (a == b) return a;

    FORD(j, LOG-1, 0) if (up[a][j] != up[b][j])
        a = up[a][j], b = up[b][j];
    return up[a][0];
}

void solve() {
    int n, Q; cin >> n >> Q;

    FOR(i, 2, n) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);
    while (Q--) {
        int u, v; cin >> u >> v;
        cout << depth[u] + depth[v] - 2 * depth[LCA(u, v)] << endl;
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
