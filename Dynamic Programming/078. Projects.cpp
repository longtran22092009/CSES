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
const int mxN = 200005;

ll dp[mxN]; // dp[i]: maximim amount before day i
vector <int> a(mxN), b(mxN), p(mxN);
map <int, int> compressed;

void solve() {
    int n; cin >> n;

    FOR(i, 0, n-1) {
        cin >> a[i] >> b[i] >> p[i];
        ++b[i];
        compressed[a[i]], compressed[b[i]];
    }

    int coords = 0;
    for (auto &x : compressed) x.se = coords++;

    vector <vector <pair <int, int>>> project(coords); // end: {start, val}
    FOR(i, 0, n-1) project[compressed[b[i]]].emplace_back(compressed[a[i]], p[i]);

    vector <ll> dp(coords, 0);
    FOR(i, 0, coords-1) {
        if (i) dp[i] = dp[i-1]; // Do nothing
        for (auto &x : project[i]) {
            // Earn money from the project end at day i
            dp[i] = max(dp[i], dp[x.fi] + x.se);
        }
    }

    cout << dp[coords - 1] << endl;
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
