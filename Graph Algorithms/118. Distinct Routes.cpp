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
const int mxN = 1005;

int n, m;
vector <int> adj[mxN], par(mxN, -1), path;
vector <pair <int, int>> g[mxN];
int capacity[mxN][mxN];
bool vis[mxN]; // Track if an edge is used or not

int bfs(int s, int t) {
    fill(all(par), -1);
    par[s] = -2;
 
    queue <pair <int, int>> q; 
    q.push({s, INF}); // {node, flow}
 
    while (!q.empty()) {
        int u = q.front().fi, currFlow = q.front().se;
        q.pop();
 
        for (auto &v : adj[u]) {
            if (par[v] == -1 && capacity[u][v] > 0) { // !vis[v]
                par[v] = u;
                int newFlow = min(currFlow, capacity[u][v]);
                if (v == t) return newFlow;
                q.push({v, newFlow});
            }
        }
    }
    return 0;
}

int maxFlow(int s, int t) {
    int totalFlow = 0;
    int newFlow = 0;
    
    while ((newFlow = bfs(s, t))) {
        totalFlow += newFlow;
        int curr = t;
        while (curr != s) {
            int pre = par[curr];
            capacity[pre][curr] -= newFlow;
            capacity[curr][pre] += newFlow;
            curr = pre;
        }
    }

    return totalFlow;
}

void findPath(int u, int t) {
    path.push_back(u);
    if (u == t) return;

    for (auto &e : g[u]) {
        int v = e.fi, id = e.se;
        if (!vis[id] && capacity[u][v] == 0) {
            vis[id] = true;
            findPath(v, t);
            return;
        }
    }
}

void solve() {
    cin >> n >> m;
    FOR(i, 1, m) {
        int u, v; cin >> u >> v;
        g[u].push_back({v, i}); // Original edges
        adj[u].push_back(v); 
        adj[v].push_back(u); // Residual edges
        capacity[u][v] += 1;
    }

    // Max-flow is the maximum day you can go from 1 to n
    int flow = maxFlow(1, n);
    cout << flow << endl;
 
    FOR(k, 1, flow) {
        path.clear();
        findPath(1, n);

        cout << sz(path) << endl;
        for (auto &x : path) cout << x << " ";
        cout << endl;
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