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
const int mxN = 3005;

char a[mxN][mxN];
bool vis[mxN][mxN];
vector <pair <int, int>> curr, nxt;
string ans = "";

void solve() {
    int n; cin >> n;
    FOR(i, 1, n) FOR(j, 1, n) cin >> a[i][j];

    curr.emplace_back(1, 1);
    ans += a[1][1];
  
    FOR(step, 2, 2*n-1) {
        char mn = '~';
        nxt.clear();

        for (auto &x : curr) {
            int i = x.fi, j = x.se;
            if (i + 1 <= n) mn = min(mn, a[i + 1][j]);
            if (j + 1 <= n) mn = min(mn, a[i][j + 1]);
        }
        
        for (auto &x : curr) {
            int i = x.fi, j = x.se;
            if (i + 1 <= n && a[i + 1][j] == mn && !vis[i + 1][j]) {
                vis[i + 1][j] = true;
                nxt.emplace_back(i + 1, j);
            }

            if (j + 1 <= n && a[i][j + 1] == mn && !vis[i][j + 1]) {
                vis[i][j + 1] = true;
                nxt.emplace_back(i, j + 1);
            }
        }

        ans += mn;
        swap(curr, nxt);
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
