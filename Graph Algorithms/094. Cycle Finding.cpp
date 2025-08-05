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

struct Edge {
    int u, v;
    ll w;
};

int n, m;
vector <Edge> edges;
vector <int> par(mxN, -1), negCycle;
vector <ll> d(mxN, 0);

void bellmanFord() {
    FOR(T, 1, n-1) {
        for (auto &e : edges) {
            int u = e.u, v = e.v;
            ll w = e.w;
            if (d[v] > d[u] + w) {
                par[v] = u;
                d[v] = d[u] + w;
            }
        }
    }
}

bool findNegCycle() {
    int negStart = -1;
    for (auto &e :edges) {
        int u = e.u, v = e.v;
        ll w = e.w;
        if (d[v] > d[u] + w) {
            par[v] = u;
            negStart = v;
            break;
        }
    }

    if (negStart == -1) return false;

    int u = negStart;
    FOR(i, 1, n) u = par[u];

    negCycle = vector <int>(1, u);
    int st = par[u];
    while (st != u) {
        negCycle.push_back(st);
        st = par[st];
    }

    negCycle.push_back(u);
    reverse(all(negCycle));
    return true;
}

void solve() {
    cin >> n >> m;
    FOR(i, 1, m) {
        int u, v; cin >> u >> v;
        ll w; cin >> w;
        edges.push_back({u, v, w});
    }

    bellmanFord();
    
    if (!findNegCycle()) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    for (auto &x : negCycle) cout << x << " ";
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
