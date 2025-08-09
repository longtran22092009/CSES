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

// Eulerian path problem
const int INF = (int) 1e9+5;
const ll LINF = (ll) 1e18;
const ll MOD = (ll) 1e9+7;
const int mxN = 200005;

int n, m;
vector <int> adj[mxN], in(mxN), out(mxN), path;

bool isEulerianPath() {
    int stNode = 0, edNode = 0;
    FOR(i, 1, n) {
        if (abs(in[i] - out[i]) > 1) return false;
        else if (in[i] - out[i] == 1) ++stNode;
        else if (out[i] - in[i] == 1) ++edNode;
    }

    // 1. All nodes have the equal in/out degree
    // 2. One stNode, edNode and other nodes have the equal in/out degree
    if ((!stNode && !edNode) || (stNode == 1 && edNode == 1)) return true;
    return false;
}

void dfs(int u) {
    while (!adj[u].empty()) {
        int node = adj[u].back();
        adj[u].pop_back();
        dfs(node);
    }
    path.push_back(u);
}

void solve() {
    cin >> n >> m;
    FOR(i, 1, m) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        ++out[u];
        ++in[v];
    }
    
    // Start at 1, end at n
    bool isStart1 = (out[1] - in[1] == 1);
    bool isEndN = (in[n] - out[n] == 1);
    
    // Check if the Eulerian path is exists
    if (!isEulerianPath() || !isStart1 || !isEndN) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    dfs(1);

    // Check for disconnected graph
    if (sz(path) == m+1) {
        reverse(all(path));
        for (auto &x : path) cout << x << " ";
    }
    else cout << "IMPOSSIBLE\n";
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
