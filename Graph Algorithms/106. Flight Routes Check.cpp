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

int n, m;
vector <int> adj[mxN], r_adj[mxN];
bool vis[mxN];
stack <int> topo;

void topoSort(int u) {
    vis[u] = true;
    for (auto &v : adj[u]) 
        if (!vis[v]) topoSort(v);
    topo.push(u);
}

void dfs(int u) {
    vis[u] = true;
    for (auto &v : r_adj[u]) 
        if (!vis[v]) dfs(v);
}

void solve() {
    cin >> n >> m;
    FOR(i, 1, m) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        r_adj[v].push_back(u);
    }

    FOR(i, 1, n) if (!vis[i]) topoSort(i);
    memset(vis, false, sizeof(vis));

    vector <int> comps;
    while (!topo.empty()) {
        int node = topo.top(); topo.pop();
        if (!vis[node]) dfs(node), comps.push_back(node);
    }

    if (sz(comps) == 1) cout << "YES\n";
    else cout << "NO\n" << comps[1] << " " << comps[0] << endl;
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
