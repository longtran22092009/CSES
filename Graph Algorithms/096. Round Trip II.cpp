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

int n, m;
vector <int> adj[mxN], par(mxN, 0), color(mxN, 0);

bool dfs(int u) {
    color[u] = 1;
    for (auto &v : adj[u]) {
        if (!color[v]) {
            par[v] = u;
            if (dfs(v)) return true;
        }
        else if (color[v] == 1) {
            vector <int> path;
            path.push_back(v);

            int s = u;
            while (s != v) {
                path.push_back(s);
                s = par[s];
            }
            path.push_back(s);

            cout << sz(path) << endl;
            reverse(all(path));
            for (auto &x : path) cout << x << " ";
            return true;
        }
    }
    color[u] = 2;
    return false;
}

void solve() {
    cin >> n >> m;
    FOR(i, 1, m) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }

    FOR(i, 1, n) if (!color[i]) {
        if (dfs(i)) return;
    }

    cout << "IMPOSSIBLE\n";
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
