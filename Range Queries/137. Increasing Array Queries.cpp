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
    vector <pair <ll, int>> tree; // {mx, id}

    segtree(int _n) {
        n = _n;
        tree.assign(4 * n, {0, 0});
    }

    pair <ll, int> combine(pair <ll, int> &a, pair <ll, int> &b) {
        if (a.fi == b.fi) return (a.se < b.se ? a : b);
        return (a.fi > b.fi ? a : b);
    }

    void build(vector <ll> &a) {
        auto self = [&](auto&& self, int v, int l, int r) -> void {
            if (r - l == 1) {
                tree[v] = {a[l], l};
                return;
            }

            int mid = (l + r) / 2;
            self(self, 2 * v, l, mid);
            self(self, 2 * v + 1, mid, r);
            tree[v] = combine(tree[2 * v], tree[2 * v + 1]);
        };
        self(self, 1, 1, n+1);
    }

    pair <ll, int> query(int ql, int qr) {
        auto self = [&](auto&& self, int ql, int qr, int v, int l, int r) -> pair <ll, int> {
            if (qr <= l || ql >= r) return {0, 0};
            if (ql <= l && r <= qr) return tree[v];

            int mid = (l + r) / 2;
            pair <ll, int> left = self(self, ql, qr, 2 * v, l, mid);
            pair <ll, int> right = self(self, ql, qr, 2 * v + 1, mid, r);
            return combine(left, right);
        };
        return self(self, ql, qr, 1, 1, n+1);
    }
};

void solve() {
    int n, Q; cin >> n >> Q;

    vector <ll> a(n+1);
    FOR(i, 1, n) cin >> a[i];

    vector <ll> pre(n+1);
    FOR(i, 1, n) pre[i] = pre[i-1] + a[i];

    vector <int> nxt(n+1), stk;
    FORD(i, n, 1) { // Next greater element
        while (!stk.empty() && a[stk.back()] <= a[i]) stk.pop_back();
        nxt[i] = (stk.empty() ? 0 : stk.back());
        stk.push_back(i);
    }

    vector <ll> suf(n+1);
    FORD(i, n, 1) {
        if (nxt[i] == 0) suf[i] = a[i] * (n - i + 1);
        else suf[i] = a[i] * (nxt[i] - i) + suf[nxt[i]];
    }

    segtree st(n);
    st.build(a);

    while (Q--) {
        int l, r; cin >> l >> r;
        pair <ll, int> res = st.query(l, r+1);

        int mxId = res.se;
        ll mxVal = res.fi;
        // totalChanges = changes in [l...mxId-1] + changes in [mxId...n]
        ll changes = (suf[l] - suf[mxId]) + mxVal * (r - mxId + 1);
        ll original = pre[r] - pre[l-1];
        // Difference between original and after changes is the answer
        ll ans = changes - original;
        cout << ans << endl;
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
