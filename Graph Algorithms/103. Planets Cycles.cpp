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
const int mxN = 200005;

struct DSU {
    int n;
    vector <int> par, rank;

    DSU(int _n) {
        n = _n;
        par.assign(n+1, 0);
        rank.assign(n+1, 1);
        iota(all(par), 0);
    }

    int find(int x) { 
        return (x == par[x] ? x : par[x] = find(par[x])); 
    }

    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (rank[a] < rank[b]) swap(a, b);
        par[b] = a;
        rank[a] += rank[b];
        return true;
    }
};

const int LOG = 31;
int n;
int up[mxN][LOG], depth[mxN], cycle[mxN];
vector <int> adj[mxN], cycleRoot;
bool vis[mxN];

void build() {
    FOR(j, 1, LOG-1) FOR(node, 1, n)
        up[node][j] = up[up[node][j-1]][j-1];
}

void dfs(int u) {
    vis[u] = true;
    for (auto &v : adj[u]) {
        if (!vis[v]) {
            depth[v] = depth[u] + 1;
            dfs(v);
        }
        else cycle[u] = depth[u] + 1;
        // Update cycle length for all node in the same cycle
        cycle[u] = max(cycle[u], cycle[v]);
    }
}

void solve() {
    cin >> n;

    DSU dsu(n);
    FOR(i, 1, n) {
        // x -> i
        int x; cin >> x;
        up[i][0] = x;
        adj[x].push_back(i);
        if (!dsu.unite(i, x)) cycleRoot.push_back(x);
    }

    build();
    for (auto &u : cycleRoot) if (!vis[u]) dfs(u);

    FOR(i, 1, n) {
        if (cycle[i]) cout << cycle[i] << " ";
        else { 
            int root = i;
            FORD(j, LOG-1, 0) {
                int curr = up[root][j];
                if (!cycle[curr]) root = curr;
            }
            root = up[root][0];

            int leafToRoot = depth[i] - depth[root];
            int dis = leafToRoot + cycle[root];
            cout << dis << " ";
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
