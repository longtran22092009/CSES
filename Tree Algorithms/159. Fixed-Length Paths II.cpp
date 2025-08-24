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
#define sz(x) (int)x.size()
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

int n, lo, hi, deepest, subDepth;
vector <int> adj[mxN], treeSize(mxN, 0);
vector <int> total_cnt(mxN, 0), cnt(mxN, 0);
bool removed[mxN];
ll ans = 0;

void dfs_sz(int u, int pre) {
    treeSize[u] = 1;
    for (auto &v : adj[u]) {
        if (v == pre || removed[v]) continue;
        dfs_sz(v, u);
        treeSize[u] += treeSize[v];
    }
}

int findCentroid(int u, int pre, int total) {
    for (auto &v : adj[u]) {
        if (v == pre || removed[v]) continue;
        if (treeSize[v] > total/2) return findCentroid(v, u, total);
    }
    return u;
}

void dfs(int u, int pre, int depth) {
    if (depth > hi) return;

    subDepth = max(subDepth, depth);
    ++cnt[depth];

    for (auto &v : adj[u]) {
        if (v == pre || removed[v]) continue;
        dfs(v, u, depth+1);
    }
}

void process(int c) {
    deepest = 0;
    ll partialInit = (lo == 1 ? 1LL : 0LL);

    for (auto &v : adj[c]) {
        if (removed[v]) continue;
        subDepth = 0;
        dfs(v, c, 1);

        ll partialSum = partialInit;
        FOR(depth, 1, subDepth) {
            ans += partialSum * 1LL * cnt[depth];

            if (hi - depth >= 0) 
                partialSum -= total_cnt[hi - depth];
            if (lo - depth - 1 >= 0) 
                partialSum += total_cnt[lo - depth - 1];
        }

        int L = max(0, lo-1);
        int R = max(hi-1, subDepth);
        FOR(depth, L, R) partialInit += cnt[depth];

        FOR(depth, 1, subDepth) total_cnt[depth] += cnt[depth];
        deepest = max(deepest, subDepth);

        fill(cnt.begin()+1, cnt.begin()+subDepth+1, 0);
    }

    fill(total_cnt.begin()+1, total_cnt.begin()+deepest+1, 0);
}

void decompose(int u) {
    dfs_sz(u, 0);
    int c = findCentroid(u, 0, treeSize[u]);
    removed[c] = true;

    process(c);
    for (auto &v : adj[c]) {
        if (!removed[v]) decompose(v);
    }
}

void solve() {
    cin >> n >> lo >> hi;
    FOR(i, 1, n-1) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    total_cnt[0] = 1;
    decompose(1);
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
