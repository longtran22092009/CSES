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

struct Fenwick {
    int n;
    vector <int> bit;

    Fenwick(int _n) {
        n = _n;
        bit.assign(n+1, 0);
    }

    void update(int idx, int val) {
        for(; idx <= n; idx += LASTBIT(idx))
            bit[idx] += val;
    }

    int query(int idx) {
        int sum = 0;
        for (; idx > 0; idx -= LASTBIT(idx))
            sum += bit[idx];
        return sum;
    }

    int range_query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l-1);
    }
};

void solve() {
    int n, Q; cin >> n >> Q;

    vector <int> a(n+1);
    FOR(i, 1, n) cin >> a[i];

    vector <int> tmp = a;
    compress(tmp);
    FOR(i, 1, n) a[i] = lower_bound(all(tmp), a[i]) - tmp.begin() + 1; // 1-based

    vector <array <int, 3>> queries; // {r, l, id}
    FOR(q, 1, Q) {
        int l, r; cin >> l >> r;
        queries.push_back({r, l, q});
    }
    sort(all(queries));
    
    int m = sz(tmp);
    vector <int> lastId(m+1, 0), ans(Q+1);
    Fenwick bit(n);

    int curr = 1;
    for (auto &q : queries) {
        int l = q[1], r = q[0], id = q[2];

        while (curr <= r) {
            int x = a[curr];
            if (lastId[x]) bit.update(lastId[x], -1);
            bit.update(curr, 1);
            lastId[x] = curr;
            ++curr;
        }
        ans[id] = bit.range_query(l, r);
    }

    FOR(q, 1, Q) cout << ans[q] << endl;
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
