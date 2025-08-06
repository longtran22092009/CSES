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

const int LOG = 31;
int n, Q;
int up[mxN][LOG], depth[mxN], comp[mxN];
vector <int> adj[mxN], cycle(mxN), cycleRoots;
bool vis[mxN];

// DSU
struct DSU {
    int n;
    vector <int> p, rank;

    DSU(int _n) {
        n = _n;
        p.assign(n+1, 0);
        rank.assign(n+1, 1);
        iota(all(p), 0);
    }

    int find(int x) { 
        return p[x] == x ? x : p[x] = find(p[x]);
    }

    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (rank[a] < rank[b]) swap(a, b);
        p[b] = a;
        rank[a] += rank[b];
        return true;
    }
};

// Binary lifting
void build() {
    FOR(j, 1, LOG-1) FOR(node, 1, n) 
        up[node][j] = up[up[node][j-1]][j-1];
}

int getAncestor(int node, int k) {
    FOR(j, 0, LOG-1) if (BIT(k, j))
        node = up[node][j];
    return node;
}

void dfs(int u, int id) {
    vis[u] = true;
    comp[u] = id;
    
    for (auto &v : adj[u]) {
        if (!vis[v]) {
            depth[v] = depth[u] + 1;
            dfs(v, id);
        }
        else cycle[u] = depth[u] + 1;

        // Update the cycle length
        cycle[u] = max(cycle[u], cycle[v]); 
    }
}

// Query
int query(int u, int v) {
    if (u == v) return 0;
    if (comp[u] != comp[v]) return -1; // Different components

    if (cycle[u]) {
        if (!cycle[v]) return -1; // u from cycle cannot go back to v on tree
        else return mod(depth[u] - depth[v], cycle[u]); // Both u and v are in the same cycle
    }

    // Both u and v are on some tree
    if (!cycle[u] && !cycle[v]) {
        if (depth[u] <= depth[v]) return -1; // u cannot turn back to v
        int dis = depth[u] - depth[v];
        return (getAncestor(u, dis) == v ? dis : -1); // a and b in the same branch else -1
    }

    // u is on tree and v is in the cycle
    int root = u;
    // Find the root of the u's tree
    FORD(j, LOG-1, 0) {
        int curr = up[root][j];
        if (!cycle[curr]) root = curr;
    }
    root = up[root][0];

    int uToRoot = depth[u] - depth[root];
    int dis = mod(depth[root] - depth[v], cycle[root]);
    return uToRoot + dis;
}

void solve() {
    cin >> n >> Q;

    DSU dsu(n);
    FOR(i, 1, n) {
        int x; cin >> x;
        up[i][0] = x;
        adj[x].push_back(i);
        if (!dsu.unite(i, x)) cycleRoots.push_back(x);
    }

    build();
    int id = 1;
    for (auto &i : cycleRoots) {
        cerr << i << endl;
        if (!vis[i]) dfs(i, id++);
    }

    while (Q--) {
        int u, v; cin >> u >> v;
        cout << query(u, v) << endl;
    }

    FOR(i, 1, n) cerr << cycle[i] << " ";
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
