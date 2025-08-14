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
const int mxN = 5000005;

int Lc[mxN], Rc[mxN];
ll sum[mxN];

struct segtree {
    int n, ptr;

    segtree(int _n) : n(_n), ptr(0) {}

    int makeNode(ll val, int L, int R) {
        int id = ++ptr;
        sum[id] = val;
        Lc[id] = L;
        Rc[id] = R;
        return id;
    }

    int update(int pre, int pos, ll val) {
        auto self = [&](auto&& self, int pre, int pos, ll val, int l, int r) -> int {
            if (r - l == 1) return makeNode(sum[pre] + val, 0, 0);

            int mid = (l + r) / 2;
            int L = Lc[pre];
            int R = Rc[pre];
            if (pos < mid) {
                int nL = self(self, L, pos, val, l, mid);
                return makeNode(sum[nL] + sum[R], nL, R);
            }
            else {
                int nR = self(self, R, pos, val, mid, r);
                return makeNode(sum[L] + sum[nR], L, nR);
            }
        };
        return self(self, pre, pos, val, 1, n+1);
    }

    ll query(int node, int ql, int qr) {
        auto self = [&](auto&& self, int node, int ql, int qr, int l, int r) -> ll {
            if (!node || qr <= l || ql >= r) return 0LL;
            if (ql <= l && r <= qr) return sum[node];

            int mid = (l + r) / 2;
            ll s1 = self(self, Lc[node], ql, qr, l, mid);
            ll s2 = self(self, Rc[node], ql, qr, mid, r);
            return s1 + s2;
        };
        return self(self, node, ql, qr, 1, n+1);
    }
};

void solve() {
    /*
        # Idea:
        S(x): Sum of all coins in [L, R] with value of each coin <= x
        For a [L, R] query, we will solve it greedily:
        - Initially, t = 0
        - While answer is not found :
            + Each time calculate currSum = S(t+1)
            + If (currSum <= t) <=> missing t+1 => ans = t+1 
            + Else t = currSum, continue the loop

        # Optimization:
        Sort all values in increasing order with original index (coin -> {value, index})
        Build versions:
        - version[i]: version[i-1] after coins[i]
        - version[i] contain all coins[1..i], coins[i] is largest
        To find S(X), first we find pos = upper_bound(all(coins), X) - coins.begin()
        pos will be the number of coins have value <= X
        which mean that version[pos] is the version that include all these coins
        ==> We can do these operations in O(log n) with Persistent Segment Tree
    */

    int n, Q; cin >> n >> Q;

    vector <ll> a(n+1);
    FOR(i, 1, n) cin >> a[i];

    // Sorting
    vector <pair <ll, int>> coins; // {val, id}
    FOR(i, 1, n) coins.push_back({a[i], i});
    sort(all(coins));

    vector <ll> vals;
    for (auto &x : coins) vals.push_back(x.fi);

    // Build versions
    segtree st(n);
    vector <int> version(n+1, 0);
    FOR(i, 1, n) {
        int pos = coins[i-1].se;
        ll val = coins[i-1].fi;
        version[i] = st.update(version[i-1], pos, val);
    }

    // Queries
    while (Q--) {
        int l, r; cin >> l >> r;

        ll t = 0;
        while (true) {
            int pos = upper_bound(all(vals), t+1) - vals.begin();
            ll S = st.query(version[pos], l, r+1);

            if (S <= t) {
                cout << t+1 << endl;
                break;
            }
            t = S;
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