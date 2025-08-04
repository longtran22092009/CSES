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

int n, m;
ll dp[mxN][MASK(10)];
// dp[col][mask]: at col the status is mask
// bit 1 presents tiles was filled by the horizontal tile from the col-1
// while bit 0 is unfilled tiles need to be process

void Try(int pos, int mask, int next_mask, vector <int> &nxt) {
    if (pos == n) {
        nxt.push_back(next_mask);
        return;
    }

    if (BIT(mask, pos)) {
        // Already filled -> go to the next one
        Try(pos + 1, mask, next_mask, nxt);
    } 
    else {
        // Try to fill with vertical tile (2x1)
        if (pos + 1 < n && !BIT(mask, pos + 1)) 
            Try(pos + 2, mask, next_mask, nxt);

        // Try to fill with horizontal tile (1x2)
        Try(pos + 1, mask, ON(next_mask, pos), nxt); 
        // ON(next_mask, pos) -> the tile at [col+1][pos] is filled
    }
}

void solve() {
    cin >> n >> m;
    dp[0][0] = 1;

    FOR(col, 0, m-1) FOR(mask, 0, MASK(n)-1) {
        if (dp[col][mask] == 0) continue;

        vector <int> nxt;
        Try(0, mask, 0, nxt);

        for (auto &nmask : nxt) 
            // # ways to fill col+1 at nmask = # ways to fill col at mask
            // with nmask is status that can be made by mask
            dp[col + 1][nmask] = (dp[col + 1][nmask] + dp[col][mask]) % MOD;
    }

    // dp[m][0]: column m without filled tiles -> n*m grid is filled correctly
    cout << dp[m][0] << endl;
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
