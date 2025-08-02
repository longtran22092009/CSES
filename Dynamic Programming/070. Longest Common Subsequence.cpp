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
const int mxN = 1005;

ll dp[mxN][mxN];

void solve() {
    int n, m; cin >> n >> m;

    vector <int> a(n), b(m);
    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;

    FOR(i, 1, n) FOR(j, 0, m) {
        if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
        else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
    }
    
    int x = n, y = m;
    vector <int> ans;
    while (x != 0 && y != 0) {
        if (a[x-1] == b[y-1]) {
            ans.push_back(a[x-1]);
            --x, --y;
        }
        else if (dp[x-1][y] >= dp[x][y-1]) --x;
        else --y;
    }
    
    reverse(all(ans));
    cout << dp[n][m] << endl;
    for (auto &x : ans) cout << x << " ";
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
