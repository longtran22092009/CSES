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

// Maximum Cardinality Bipartite Matching (MCBM)
const int INF = (int) 1e9+5;
const ll LINF = (ll) 1e18;
const ll MOD = (ll) 1e9+7;
const int mxN = 100005;

int n, m, k;
vector <int> adj[mxN], match(mxN, -1), getMatched(mxN, -1);
// matchA[u]: the vertex that is matched from u
// matchB[v]: the vertex that match to v
bool vis[mxN];

bool Kuhn(int u) {
    if (vis[u]) return false;
    vis[u] = true;

    for (auto &v : adj[u]) {
        // v is not already matched
        // Or can somehow match u with v
        if (getMatched[v] == -1 || Kuhn(getMatched[v])) {
            match[u] = v;
            getMatched[v] = u;
            return true;
        }
    }
    return false;
}

void solve() {
    cin >> n >> m >> k;
    FOR(i, 1, k) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }

    int ans = 0;
    FOR(u, 1, n) {
        fill(all(vis), false);
        if (Kuhn(u)) ++ans;
    }

    cout << ans << endl;
    FOR(u, 1, n)
        if (match[u] != -1) // Matched to another vertex
            cout << u << " " << match[u] << endl;
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
