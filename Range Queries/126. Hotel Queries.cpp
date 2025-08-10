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

struct segtree {
    int n;
    vector <ll> tree;
 
    segtree(int _n) {
        n = _n + 1;
        tree.assign(4 * n, 0);
    }
 
    void build(vector <int> &a) {
        auto self = [&](auto&& self, int v, int l, int r) -> void {
            if (r - l == 1) {
                tree[v] = 1LL * a[l];
                return;
            }
 
            int mid = (l + r) / 2;
            self(self, 2 * v, l, mid);
            self(self, 2 * v + 1, mid, r);
            tree[v] = max(tree[2 * v], tree[2 * v + 1]);
        };
        self(self, 1, 1, n);
    }
    
    void update(int pos, int val) {
        auto self = [&](auto&& self, int pos, int val, int v, int l, int r) -> void {
            if (r - l == 1) {
                tree[v] -= val;
                return;
            }
 
            int mid = (l + r) / 2;
            if (pos < mid) self(self, pos, val, 2 * v, l, mid);
            else self(self, pos, val, 2 * v + 1, mid, r);
            tree[v] = max(tree[2 * v], tree[2 * v + 1]);
        };
        self(self, pos, val, 1, 1, n);
    }
 
    int query(int x) {
        auto self = [&](auto&& self, int x, int v, int l, int r) -> int {
            if (tree[v] < x) return -1;
            if (r - l == 1) return l;
 
            int mid = (l + r) / 2;
            int res = self(self, x, 2 * v, l, mid);
            if (res != -1) return res;
            return self(self, x, 2 * v + 1, mid, r);
        };
        return self(self, x, 1, 1, n);
    }
};
 
void solve() {
    int n, Q; cin >> n >> Q;
 
    vector <int> a(n+1);
    FOR(i, 1, n) cin >> a[i];
 
    segtree st(n);
    st.build(a);

    while (Q--) {
        int x; cin >> x;
        int id = st.query(x);
        if (id != -1) st.update(id, x);
        cout << (id == -1 ? 0 : id) << " ";
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
