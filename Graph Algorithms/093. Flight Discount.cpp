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
vector <pair <int, int>> adj[mxN], r_adj[mxN];
vector <ll> d1(mxN, LINF), dn(mxN, LINF);

void Dijkstra(int s, vector <ll> &d, vector <pair <int, int>> adj[]) {
    priority_queue <pair <ll, int>, vector <pair <ll, int>>, greater<>> q;
    q.push({0, s});
    d[s] = 0;

    while (!q.empty()) {
        int u = q.top().se;
        ll dis = q.top().fi;
        q.pop();

        if (dis > d[u]) continue;
        for (auto &x : adj[u]) {
            int v = x.fi, w = x.se;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                q.push({d[v], v});
            }
        }
    }
}

void solve() {
    cin >> n >> m;
    FOR(i, 1, m) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w});
        r_adj[v].push_back({u, w});
    }

    Dijkstra(1, d1, adj);
    Dijkstra(n, dn, r_adj);

    ll ans = LINF;
    FOR(i, 1, n) for (auto &x : adj[i]) 
        ans = min(ans, d1[i] + x.se/2 + dn[x.fi]);

    cout << ans << endl;
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
