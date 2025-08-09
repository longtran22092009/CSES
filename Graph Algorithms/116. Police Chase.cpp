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

// Max-flow Min-cut problem
const int INF = (int) 1e9+5;
const ll LINF = (ll) 1e18;
const ll MOD = (ll) 1e9+7;
const int mxN = 505;

int n, m;
vector <int> adj[mxN], par(mxN, -1);
int capacity[mxN][mxN];

int bfs(int s, int t) {
    fill(all(par), -1);
    par[s] == -2;

    queue <pair <int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int u = q.front().fi, currFlow = q.front().se;
        q.pop();
        
        if (u == t) return currFlow;
        for (auto &v : adj[u]) {
            if (par[v] == -1 && capacity[u][v] > 0) {
                int newFlow = min(currFlow, capacity[u][v]);
                par[v] = u;
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

vector <pair <int, int>> findMinCut(int s) {
    vector <bool> vis(mxN, false);
    queue <int> q; q.push(s);
    vis[s] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();

        for (auto &v : adj[u]) {
            if (!vis[v] && capacity[u][v] > 0) {
                vis[v] = true;
                q.push(v);
            }
        }
    }

    vector <pair <int, int>> res;
    FOR(u, 1, n) if (vis[u]) {
        for (auto &v : adj[u]) 
            if (!vis[v] && !capacity[u][v]) res.push_back({u, v});
    }

    return res;
}

void solve() {
    cin >> n >> m;
    FOR(i, 1, m) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        capacity[u][v] += 1;
        capacity[v][u] += 1;
    }

    int flow = maxFlow(1, n);
    vector <pair <int, int>> cuts = findMinCut(1);

    cout << flow << endl;
    for (auto &x : cuts) cout << x.fi << " " << x.se << endl;
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
