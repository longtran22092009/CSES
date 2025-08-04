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
const int mxN = 20; // 20 digit
 
ll memo[mxN][11][2][2];
// pos, prev+1 (-1..9 -> 0..10), tight, leading_zero
 
ll dp(int pos, int prev, bool tight, bool leading_zero, string &s) {
    // Base case:
    if (pos == sz(s)) return 1;
    // Memoization
    ll &res = memo[pos][prev+1][tight][leading_zero];
    if (res != -1) return res;
    res = 0;
    
    int limit = (tight ? s[pos] - '0' : 9);
    FOR(d, 0, limit) {
        if (!leading_zero && d == prev) continue;

        bool isTight = tight && (d == s[pos] - '0');
        bool isLeadingZero = leading_zero && (d == 0);
        int newPrev = (isLeadingZero ? -1 : d);

        res += dp(pos+1, newPrev, isTight, isLeadingZero, s);
    }

    return res;
}

ll calculate(string &s) {
    memset(memo, -1, sizeof(memo));
    return dp(0, -1, 1, 1, s);
}
 
void solve() {
    string a, b; cin >> a >> b;
    string lb = to_string(stoll(a) - 1);
    ll ans = calculate(b) - calculate(lb);
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