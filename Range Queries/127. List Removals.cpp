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
    vector <int> tree;

    segtree(int _n) {
        n = _n + 1;
        tree.assign(4 * n, 0);
    }

    void build() {
        auto self = [&](auto&& self, int v, int l, int r) -> void {
            if (r - l == 1) {
                tree[v] = 1;
                return;
            }

            int mid = (l + r) / 2;
            self(self, 2 * v, l, mid);
            self(self, 2 * v + 1, mid, r);
            tree[v] = tree[2 * v] + tree[2 * v + 1];
        };
        self(self, 1, 1, n);
    }

    void update(int pos) {
        auto self = [&](auto&& self, int pos, int v, int l, int r) -> void {
            if (r - l == 1) {
                tree[v] = 0;
                return;
            }

            int mid = (l + r) / 2;
            if (pos < mid) self(self, pos, 2 * v, l, mid);
            else self(self, pos, 2 * v + 1, mid, r);
            tree[v] = tree[2 * v] + tree[2 * v + 1];
        };
        self(self, pos, 1, 1, n);
    }

    int query(int k) {
        auto self = [&](auto&& self, int k, int v, int l, int r) -> int {
            if (r - l == 1) return l;

            int mid = (l + r) / 2;
            if (tree[2 * v] >= k) return self(self, k, 2 * v, l, mid);
            else return self(self, k - tree[2 * v], 2 * v + 1, mid, r);
        };
        return self(self, k, 1, 1, n);
    }
};

void solve() {
    int n; cin >> n;

    vector <int> a(n+1);
    FOR(i, 1, n) cin >> a[i];

    segtree st(n);
    st.build();

    FOR(i, 1, n) {
        int k; cin >> k;
        int id = st.query(k);
        cout << a[id] << " ";
        st.update(id);
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
