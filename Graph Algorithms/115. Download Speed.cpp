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

// Max-flow problem
const int INF = (int) 1e9+5;
const ll LINF = (ll) 1e18;
const ll MOD = (ll) 1e9+7;
const int mxN = 505;

int n, m;
vector <int> adj[mxN], par(mxN, -1);
ll capacity[mxN][mxN];

ll bfs(int s, int t) {
    fill(all(par), -1);
    par[s] = -2;

    queue <pair <int, ll>> q;
    q.push({s, LINF});

    while (!q.empty()) {
        int u = q.front().fi;
        ll currFlow = q.front().se;
        q.pop();

        if (u == t) return currFlow;
        for (auto &v : adj[u]) {
            if (par[v] == -1 && capacity[u][v] > 0) {
                ll newFlow = min(currFlow, capacity[u][v]);
                par[v] = u;
                q.push({v, newFlow});
            }
        }
    }

    return 0;
}

ll maxFlow(int s, int t) {
    ll totalFlow = 0;
    ll newFlow = 0;

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

void solve() {
    cin >> n >> m;
    FOR(i, 1, m) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back(v);
        adj[v].push_back(u); // Residual edges
        capacity[u][v] += w;
    }

    ll ans = maxFlow(1, n);
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
