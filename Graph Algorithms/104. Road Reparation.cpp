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
const int mxN = 100005;

struct DSU {
    int n;
    vector <int> par, rank;

    DSU(int _n) {
        n = _n;
        par.assign(n+1, 0);
        rank.assign(n+1, 1);
        iota(all(par), 0);
    }

    int find(int x) {
        return (x == par[x] ? x : par[x] = find(par[x]));
    }

    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if(a == b) return false;
        if (rank[a] < rank[b]) swap(a, b);
        par[b] = a;
        rank[a] += rank[b];
        return true;
    }
};

int n, m;
vector <array <int, 3>> edges; // {w, u, v}

void Kruskal() {
    DSU dsu(n);
    vector <array <int, 3>> MST;
    ll d = 0;

    sort(all(edges));
    for (auto &e : edges) {
        if (sz(MST) == n-1) break;

        int u = e[1], v = e[2], w = e[0];
        if (dsu.unite(u, v)) {
            MST.push_back(e);
            d += w;
        }
    }

    if (sz(MST) == n-1) cout << d << endl;
    else cout << "IMPOSSIBLE\n";
}

void solve() {
    cin >> n >> m;
    FOR(i, 1, m) {
        int u, v, w; cin >> u >> v >> w;
        edges.push_back({w, u, v});
    }

    Kruskal();
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
