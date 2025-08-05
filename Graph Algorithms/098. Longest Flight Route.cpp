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

int n, m, ans = 0;
vector <int> adj[mxN], par(mxN, -1);
vector <int> topo, d(mxN, -1);
bool vis[mxN];

void dfs(int u) {
    vis[u] = true;
    for (auto &v : adj[u]) if (!vis[v]) dfs(v);
    topo.push_back(u);
}

void solve() {
    cin >> n >> m;
    FOR(i, 1, m) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }

    // Topo sort and reverse order to ensure u will 
    // be calculated before all v (u is parent of v)
    FOR(i, 1, n) if (!vis[i]) dfs(i);
    reverse(all(topo));

    d[1] = 1;
    for (auto &u : topo) {
        for (auto &v : adj[u]) {
            if (d[u] != -1 && d[v] < d[u] + 1) {
                d[v] = d[u] + 1;
                par[v] = u;
            }
        }
    }

    if (d[n] == -1) cout << "IMPOSSIBLE\n";
    else {
        vector <int> path;
        int s = n;
        while (s != 1) {
            path.push_back(s);
            s = par[s];
        }
        path.push_back(s);

        cout << d[n] << endl;
        reverse(all(path));
        for (auto &x : path) cout << x << " ";
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
