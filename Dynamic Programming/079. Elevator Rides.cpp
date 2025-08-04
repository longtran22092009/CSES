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
const int mxN = 20;

void solve() {
    int n, limit; cin >> n >> limit;

    vector <int> w(n);
    for (auto &x : w) cin >> x;

    vector <pair <int, int>> dp(MASK(n), {INF, 0}); // {rides, weights}
    dp[0] = {1, 0};
    FOR(mask, 1, MASK(n)-1) {
        FOR(i, 0, n-1) if (BIT(mask, i)) {
            int lst = OFF(mask, i);
            int rides = dp[lst].fi;
            int weights = dp[lst].se;

            if (weights + w[i] > limit) ++rides, weights = min(weights, w[i]);
            else weights += w[i];

            dp[mask] = min(dp[mask], {rides, weights});
        }
    }

    cout << dp[MASK(n)-1].fi << endl;
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
