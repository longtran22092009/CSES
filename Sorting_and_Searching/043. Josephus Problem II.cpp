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
#define all(x) begin(x), end(x)
#define mod(x, k) ((((x) % (k)) + (k)) % (k))
#define compress(c) sort(all(c)); c.erase(unique(all(c)), c.end());
#define Longgggg ios_base::sync_with_stdio(0); cin.tie(0);
#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define FORD(i, a, b) for (int i = (a); i >= (b); i--)
//====== FILE ======//
#define IN "A.in"
#define OUT "A.out"
#define DEBUG "debug.out"
//==================//

const int INF = (int) 1e9+5;
const ll LINF = (ll) 1e18;
const ll MOD = (ll) 1e9+7;
const int mxN = 200005;

// Tree node v represents [l, r)
struct segtree {
    int N;
    vector <ll> tree;

    segtree(int n) {
        N = n;
        tree.assign(4 * N, 0ll);
    }

    void build() {
        auto self = [&](auto&& self, int v, int l, int r) -> void {
            if (r - l == 1) {
                tree[v] = 1;
                return;
            }

            int mid = (l + r) / 2;
            self(self, 2 * v + 1, l, mid);
            self(self, 2 * v + 2, mid, r);

            tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
        };
        self(self, 0, 0, N);
    }

    void update(int pos) {
        auto self = [&](auto&& self, int pos, int v, int l, int r) -> void {
            if (r - l == 1) {
                tree[v] = 0;
                return;
            }

            int mid = (l + r) / 2;
            if (pos < mid) self(self, pos, 2 * v + 1, l, mid);
            else self(self, pos, 2 * v + 2, mid, r);

            tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
        };
        self(self, pos, 0, 0, N);
    }

    int query(int k) {
        auto self = [&](auto&& self, int k, int v, int l, int r) -> int {
            if (r - l == 1) return l;
            int mid = (l + r) / 2;
            if (tree[2 * v + 1] > k) return self(self, k, 2 * v + 1, l, mid);
            return self(self, k - tree[2 * v + 1], 2 * v + 2, mid, r);
        };
        return self(self, k, 0, 0, N);
    }
};

void solve() {
    int n, k; cin >> n >> k;

    int alive = n, pos = 0;
    segtree st(n);
    st.build();

    FOR(i, 1, n) {
        pos = mod(pos + k, alive);
        int id = st.query(pos);
        cout << id + 1 << " ";
        st.update(id);
        --alive;
    }
    cout << endl;
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
