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
vector <int> coins(mxN), comp(mxN);
vector <int> adj[mxN], r_adj[mxN], scc_adj[mxN];
stack <int> topo;
bool vis[mxN];
ll dp[mxN], sum[mxN];

void topoSort(int u) {
    vis[u] = true;
    for (auto &v : adj[u])
        if (!vis[v]) topoSort(v);
    topo.push(u);
}

void dfs(int u, int id) {
    vis[u] = true;
    comp[u] = id;
    for (auto &v : r_adj[u])
        if (!vis[v]) dfs(v, id);
}

// Dp on tree
void travel(int u) {
    vis[u] = true;
    dp[u] = sum[u];
    for (auto &v : scc_adj[u]) {
        if (!vis[v]) travel(v);
        dp[u] = max(dp[u], dp[v] + sum[u]);
    }
}

void solve() {
    cin >> n >> m;
    FOR(i, 1, n) cin >> coins[i];
    FOR(i, 1, m) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        r_adj[v].push_back(u);
    }

    // Find all SCCs
    FOR(i, 1, n) if (!vis[i]) topoSort(i);
    fill(vis, vis + mxN, false);

    int id = 0;
    while (!topo.empty()) {
        int node = topo.top(); topo.pop();
        if (!vis[node]) dfs(node, ++id);
    }

    // Calculate sum of each SCCs
    FOR(i, 1, n) sum[comp[i]] += coins[i];

    // Build graph between SCCs
    FOR(u, 1, n) for (auto &v : adj[u]) {
        if (comp[u] != comp[v]) 
            scc_adj[comp[u]].push_back(comp[v]);
    }

    // Using dp to find the answer
    fill(vis, vis + mxN, false);
    FOR(i, 1, id) if (!vis[i]) travel(i);

    ll ans = *max_element(dp, dp + id + 1);
    cout << ans << endl;
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
