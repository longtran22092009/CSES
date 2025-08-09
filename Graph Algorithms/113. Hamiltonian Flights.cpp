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
const int mxN = 21;

int n, m;
vector <int> adj[mxN];
ll dp[MASK(mxN)][mxN];
// dp[mask][u]: # routes with bit 1 in mask is visited city and currently at city u 

void solve() {
    cin >> n >> m;
    FOR(i, 1, m) {
        int u, v; cin >> u >> v;
        --u, --v; // 0-based
        adj[u].push_back(v);
    }

    dp[1][0] = 1; // Start from city 1
    FOR(mask, 1, MASK(n)-1) {
        // visit other city before city 1
        if (!BIT(mask, 0)) continue; 
        // visit city n before other city
        if (BIT(mask, n-1) && mask != MASK(n-1)) continue; 

        FOR(u, 0, n-1) if (BIT(mask, u)) { // vis[u]
            for (auto &v : adj[u]) if (!BIT(mask, v)) { // !vis[v]
                int nxt = ON(mask, v);
                dp[nxt][v] = (dp[nxt][v] + dp[mask][u]) % MOD;
            }
        }
    }

    cout << dp[MASK(n)-1][n-1] << endl;
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
