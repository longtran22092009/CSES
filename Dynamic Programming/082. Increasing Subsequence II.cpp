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
    int N;
    vector<ll> bit;

    Fenwick(int n) { // 1-based
        N = n;
        bit.assign(N + 1, 0);
    }

    // Cộng thêm val vào vị trí idx
    void update(int idx, ll val) {
        for (; idx <= N; idx += LASTBIT(idx))
            bit[idx] = (bit[idx] + val) % MOD;
    }

    // Tính tổng từ 1 đến idx
    ll query(int idx) {
        ll res = 0;
        for (; idx > 0; idx -= LASTBIT(idx))
            res = (res + bit[idx]) % MOD;
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

    vector <int> a(n), tmp;
    for (auto &x : a) {
        cin >> x;
        tmp.push_back(x);
    }

    compress(tmp);
    map <int, int> coords;
    FOR(i, 0, sz(tmp)-1) coords[tmp[i]] = i+1;

    Fenwick bit(sz(tmp)+1);
    ll ans = 0;
    FOR(i, 0, n-1) {
        int id = coords[a[i]];
        // dp[i] = 1 (only a[i]) + sum(dp[j])
        ll cnt = 1 + bit.query(id - 1); // bit[1..id-1]: strictly smaller
        bit.update(id, cnt);
        ans = (ans + cnt) % MOD;
    }

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
