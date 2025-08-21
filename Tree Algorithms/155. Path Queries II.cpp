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
const int mxN = (int) 2e5+5;

// Tree node v represents [l, r)
struct segtree {
    int n;
    vector <int> tree;

    segtree(int _n) {
        n = _n;
        tree.assign(4 * n, -INF);
    }

    void build(vector <int> &a, int v, int l, int r) {
        if (r - l == 1) {
            tree[v] = a[l];
            return;
        }
        
        int mid = (l + r) / 2;
        build(a, 2 * v, l, mid);
        build(a, 2 * v + 1, mid, r);
        tree[v] = max(tree[2 * v], tree[2 * v + 1]);
    };
    
    void update(int pos, int val, int v, int l, int r) {
        if (r - l == 1) {
            tree[v] = val;
            return;
        }
        
        int mid = (l + r) / 2;
        if (pos < mid) update(pos, val, 2 * v, l, mid);
        else update(pos, val, 2 * v + 1, mid, r);
        tree[v] = max(tree[2 * v], tree[2 * v + 1]);
    }
    
    int query(int ql, int qr, int v, int l, int r) {
        if (qr <= l || ql >= r) return -INF;
        if (ql <= l && r <= qr) return tree[v];
        
        int mid = (l + r) / 2;
        int s1 = query(ql, qr, 2 * v, l, mid);
        int s2 = query(ql, qr, 2 * v + 1, mid, r);
        return max(s1, s2);
    }
    
    void build(vector <int> &a) { build(a, 1, 1, n+1); }

    void update(int pos, int val) { update(pos, val, 1, 1, n+1); }

    int query(int ql, int qr) { return query(ql, qr, 1, 1, n+1); }
};

int n, Q, timeDfs = 0;
vector <int> adj[mxN];
int depth[mxN], par[mxN], treeSize[mxN];
int heavy[mxN], head[mxN], pos[mxN];
segtree st(0);

void dfs(int u, int pre) {
    treeSize[u] = 1;

    int best = 0;
    for (auto &v : adj[u]) {
        if (v == pre) continue;
        par[v] = u;
        depth[v] = depth[u] + 1;
        dfs(v, u);

        treeSize[u] += treeSize[v];
        if (treeSize[v] > best) {
            best = treeSize[v];
            heavy[u] = v;
        }
    }
}

void Hld(int u, int h) {
    head[u] = h;
    pos[u] = ++timeDfs;

    if (heavy[u] != -1) { // Not leaf
        Hld(heavy[u], h); // Continue the heavy chain
        for (auto &v : adj[u]) {
            if (v == par[u] || v == heavy[u]) continue;
            Hld(v, v); // Start a new heavy chain
        }
    }
}

int cal(int u, int v) {
    int res = -INF;
    while (head[u] != head[v]) {
        if (depth[head[u]] < depth[head[v]]) swap(u, v);
        res = max(res, st.query(pos[head[u]], pos[u]+1));
        u = par[head[u]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    res = max(res, st.query(pos[u], pos[v]+1));
    return res;
}

void solve() {
    cin >> n >> Q;

    vector <int> a(n+1);
    FOR(i, 1, n) cin >> a[i];

    FOR(i, 1, n-1) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    fill(heavy, heavy + mxN, -1);
    dfs(1, 0);
    Hld(1, 1);

    vector <int> b(n+1);
    FOR(i, 1, n) b[pos[i]] = a[i];

    st = segtree(n);
    st.build(b);

    while (Q--) {
        int op; cin >> op;

        if (op == 1) {
            int p, v; cin >> p >> v;
            st.update(pos[p], v);
        }
        else {
            int u, v; cin >> u >> v;
            cout << cal(u, v) << " ";    
        }
    }
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
