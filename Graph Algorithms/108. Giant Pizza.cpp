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


// 2-SAT problem (Boolean satisfiability)
const int INF = (int) 1e9+5;
const ll LINF = (ll) 1e18;
const ll MOD = (ll) 1e9+7;
const int mxN = 200005;

int n, m;
// Each x will split to x and ~x
vector <int> adj[2*mxN], r_adj[2*mxN], comp(2*mxN);
bool vis[2*mxN];
stack <int> topo;

// Kosaraju
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

// 2-SAT
int NOT(int x) {
    return x + (x <= m ? m : -m);
}

void addClause(int a, int b) {
    // a OR b => ~a -> b, ~b -> a
    adj[NOT(a)].push_back(b);
    adj[NOT(b)].push_back(a);
    r_adj[b].push_back(NOT(a));
    r_adj[a].push_back(NOT(b));
}

void solve() {
    cin >> n >> m;
    FOR(i, 1, n) {
        char s1, s2;
        int x1, x2;
        cin >> s1 >> x1 >> s2 >> x2;
        
        if (s1 == '-') x1 = NOT(x1);
        if (s2 == '-') x2 = NOT(x2);
        addClause(x1, x2); // x1 OR x2
    }

    FOR(i, 1, 2*m) if (!vis[i]) topoSort(i);
    fill(vis, vis + 2*mxN, false);

    int id = 0;
    while (!topo.empty()) {
        int node = topo.top(); topo.pop();
        if (!vis[node]) dfs(node, ++id);
    }

    // Check if a and ~a is in the same SCC
    FOR(i, 1, m) {
        if (comp[i] == comp[NOT(i)]) {
            cout << "IMPOSSIBLE\n";
            return;
        }
    }

    FOR(i, 1, m) cout << (comp[i] > comp[NOT(i)] ? '+' : '-') << " ";
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
