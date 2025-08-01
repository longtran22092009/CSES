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
#define sz(x) (int)size(x)
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
const int mxN = 100005;

struct Fenwick {
    int N;
    vector<ll> bit;

    Fenwick(int n) { // 0-based
        N = n;
        bit.assign(N + 1, 0);
    }

    // Cộng thêm val vào vị trí idx
    void update(int idx, ll val) {
        for (++idx; idx <= N; idx += LASTBIT(idx)) bit[idx] += val;
    }

    // Tính tổng từ 1 đến idx
    ll query(int idx) {
        ll res = 0;
        for (++idx; idx > 0; idx -= LASTBIT(idx)) res += bit[idx];
        return res;
    }

    // Tổng từ l đến r
    ll range_query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

void solve() {
    int n; cin >> n;

    vector <array <int, 3>> seg(n);
    vector <int> coords;
    FOR(i, 0, n-1) {
        int l, r; cin >> l >> r;
        seg[i] = {l, r, i};
        coords.push_back(r);
    }

    compress(coords);
    for (auto &e : seg) e[1] = lower_bound(all(coords), e[1]) - coords.begin();

    sort(all(seg), [&](auto &a, auto &b) {
        if (a[0] != b[0]) return a[0] < b[0];
        if (a[1] != b[1]) return a[1] > b[1];
        return a[2] < b[2];
    });
    
    vector <int> a(n), b(n);
    Fenwick bit(sz(coords));

    // Contains segment
    FORD(i, n-1, 0) {
        int id = seg[i][2], r = seg[i][1];
        a[id] = bit.query(r);
        bit.update(r, 1);
    }

    bit = Fenwick(sz(coords));

    // Contained segment
    FOR(i, 0, n-1) {
        int id = seg[i][2], r = seg[i][1];
        b[id] = bit.range_query(r, sz(coords)-1);
        bit.update(r, 1);
    }

    for (auto &x : a) cout << x << " ";
    cout << endl;
    for (auto &x : b) cout << x << " ";
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
