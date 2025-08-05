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
const int mxN = 2505;

struct Edge {
    int u, v;
    ll w;
};

int n, m;
bool negCycle = false;
vector <Edge> edges;
vector <int> adj[mxN], r_adj[mxN];
vector <ll> d(mxN, LINF);
bool inNegCycle[mxN], vis1[mxN], visN[mxN];

// Check for all nodes in same component with 1 and n
void dfs1(int u) {
    vis1[u] = true;
    for (int v : adj[u]) if (!vis1[v]) dfs1(v);
}

void dfsN(int u) {
    visN[u] = true;
    for (int v : r_adj[u]) if (!visN[v]) dfsN(v);
}

void bellmanFord(int s) {
    d[s] = 0;
    FOR(T, 1, n-1) {
        for (auto &e : edges) {
            int u = e.u, v = e.v;
            ll w = e.w;

            if (d[u] != LINF && d[v] > d[u] + w)
                d[v] = d[u] + w;
        }
    }
}

void findNegCycle() {
    for (auto &e : edges) {
        int u = e.u, v = e.v;
        ll w = e.w;

        if (d[u] != LINF && d[v] > d[u] + w) {
            inNegCycle[v] = true;
            negCycle = true;
        }
    }
}

void solve() {
    cin >> n >> m;
    FOR(i, 1, m) {
        int u, v; cin >> u >> v;
        ll w; cin >> w;
        adj[u].push_back(v);
        r_adj[v].push_back(u);
        edges.push_back({u, v, -w}); 
        // Reverse weight => find max score -> find min score
    }

    bellmanFord(1);
    findNegCycle();
    dfs1(1);
    dfsN(n);

    FOR(i, 1, n) {
        if (inNegCycle[i] && vis1[i] && visN[i]) {
            // Node i is in negative cycle and affect the path from 1 to n
            cout << "-1\n";
            return;
        }
    }

    cout << -d[n] << endl; // Reverse again to get the answer
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
