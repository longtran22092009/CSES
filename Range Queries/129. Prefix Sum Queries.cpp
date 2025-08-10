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
    vector <pair <ll, ll>> tree; // {sum, prefix} 

    segtree(int _n) {
        n = _n;
        tree.assign(4 * n, {0LL, 0LL});
    }
    
    pair <ll, ll> merge(pair <ll, ll> &a, pair <ll, ll> &b) {
        return {a.fi + b.fi, max(a.se, a.fi + b.se)};
    }

    void build(vector <ll> &a) {
        auto self = [&](auto&& self, int v, int l, int r) -> void {
            if (r - l == 1) {
                tree[v] = {a[l], max(0LL, a[l])};
                return;
            }

            int mid = (l + r) / 2;
            self(self, 2 * v, l, mid);
            self(self, 2 * v + 1, mid, r);
            tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
        };
        self(self, 1, 1, n+1);
    }


    void update(int pos, int val) {
        auto self = [&](auto&& self, int pos, int val, int v, int l, int r) -> void {
            if (r - l == 1) {
                tree[v] = {val, max(0LL, 1LL * val)};
                return;
            }

            int mid = (l + r) / 2;
            if (pos < mid) self(self, pos, val, 2 * v, l, mid);
            else self(self, pos, val, 2 * v + 1, mid, r);
            tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
        };
        self(self, pos, val, 1, 1, n+1);
    }

    pair <ll, ll> query(int ql, int qr) {
        auto self = [&](auto&& self, int ql, int qr, int v, int l, int r) -> pair <ll, ll> {
            if (qr <= l || ql >= r) return {0, 0};
            if (ql <= l && r <= qr) return tree[v];

            int mid = (l + r) / 2;
            pair <ll, ll> s1 = self(self, ql, qr, 2 * v, l, mid);
            pair <ll, ll> s2 = self(self, ql, qr, 2 * v + 1, mid, r);

            return merge(s1, s2);
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
        int op; cin >> op;

        if (op == 1) {
            int k, x; cin >> k >> x;
            st.update(k, x);
        }
        else {
            int l, r; cin >> l >> r;
            cout << st.query(l, r+1).se << endl;
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
