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
    vector <ll> tree, lazyAdd, lazyAssign;

    segtree(int _n) {
        n = _n;
        tree.assign(4 * n, 0LL);
        lazyAdd.assign(4 * n, 0LL);
        lazyAssign.assign(4 * n, 0LL);
    }

    void build(vector <ll> &a) {
        auto self = [&](auto&& self, int v, int l, int r) -> void {
            if (r - l == 1) {
                tree[v] = a[l];
                return;
            }

            int mid = (l + r) / 2;
            self(self, 2 * v, l, mid);
            self(self, 2 * v + 1, mid, r);
            tree[v] = tree[2 * v] + tree[2 * v + 1];
        };
        self(self, 1, 1, n+1);
    }

    void apply_add(ll val, int v, int l, int r) {
        tree[v] += val * (r - l);
        lazyAdd[v] += val;
    }

    void apply_assign(ll val, int v, int l, int r) {
        tree[v] = val * (r - l);
        lazyAssign[v] = val;
        lazyAdd[v] = 0LL;
    }

    void push(int v, int l, int r) {
        if (r - l == 1) return;

        int mid = (l + r) / 2;
        if (lazyAssign[v]) {
            apply_assign(lazyAssign[v], 2 * v, l, mid);
            apply_assign(lazyAssign[v], 2 * v + 1, mid, r);
        }

        apply_add(lazyAdd[v], 2 * v, l, mid);
        apply_add(lazyAdd[v], 2 * v + 1, mid, r);

        lazyAdd[v] = 0LL;
        lazyAssign[v] = 0LL;
    }

    void update(int ql, int qr, ll val, int op) {
        auto self = [&](auto&& self, int ql, int qr, int val, int op, int v, int l, int r) -> void {
            if (qr <= l || ql >= r) return;
            if (ql <= l && r <= qr) {
                if (op == 1) apply_add(val, v, l, r);
                else apply_assign(val, v, l, r);
                return;
            }
            
            push(v, l, r);
            int mid = (l + r) / 2;
            self(self, ql, qr, val, op, 2 * v, l, mid);
            self(self, ql, qr, val, op, 2 * v + 1, mid, r);
            tree[v] = tree[2 * v] + tree[2 * v + 1];
        };
        self(self, ql, qr, val, op, 1, 1, n+1);
    }

    ll query(int ql, int qr) {
        auto self = [&](auto&& self, int ql, int qr, int v, int l, int r) -> ll {
            if (qr <= l || ql >= r) return 0LL;
            if (ql <= l && r <= qr) return tree[v];

            push(v, l, r);
            int mid = (l + r) / 2;
            ll s1 = self(self, ql, qr, 2 * v, l, mid);
            ll s2 = self(self, ql, qr, 2 * v + 1, mid, r);
            return s1 + s2;
        };
        return self(self, ql, qr, 1, 1, n+1);
    }
};

void solve() {
    int n, Q; cin >> n >> Q;

    vector <ll> a(n+1);
    FOR(i, 1, n) cin >> a[i];

    segtree st(n);
    st.build(a);

    while (Q--) {
        int op, l, r; cin >> op >> l >> r;

        if (op == 3) cout << st.query(l, r+1) << endl;
        else {
            ll x; cin >> x;
            st.update(l, r+1, x, op);
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
