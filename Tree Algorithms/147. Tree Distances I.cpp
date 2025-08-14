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
const int mxN = (int) 2e5+5;

int n;
vector <int> adj[mxN];
int d[2][mxN]; // d[0/1][i]: distance a/b to i

void dfs(int u, int pre, int op) {
    for (auto &v : adj[u]) {
        if (v == pre) continue;
        d[op][v] += d[op][u] + 1;
        dfs(v, u, op);
    }
}

void solve() {
    // Maximum distance from a node to another node
    // is it distance to one of two end of the diameter
    cin >> n;
    FOR(i, 1, n-1) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0, 0);
    int a = max_element(d[0], d[0] + mxN) - d[0];
    fill(&d[0][0], &d[0][0] + mxN*2, 0);
    
    dfs(a, 0, 0);
    int b = max_element(d[0], d[0] + mxN) - d[0];

    dfs(b, 0, 1);
    FOR(i, 1, n) cout << max(d[0][i], d[1][i]) << " ";
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
