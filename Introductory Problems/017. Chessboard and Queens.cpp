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
#define FORE(a, b) for (auto (a) : (b))
//====== FILE ======//
#define IN "A.in"
#define OUT "A.out"
#define DEBUG "debug.out"
//==================//

const int INF = (int) 1e9+5;
const ll LINF = (ll) 1e18;
const ll MOD = (ll) 1e9+7;
const int mxN = 100005;

int grid[10][10];
bool col[10], d1[20], d2[20];
ll ans = 0;

void backtrack(int i) {
    if (i == 9) {
        ++ans;
        return;
    }

    FOR(j, 1, 8) {
        if (grid[i][j]) continue;
        if (col[j] || d1[i - j + 8] || d2[i + j - 1]) continue;

        col[j] = d1[i - j + 8] = d2[i + j - 1] = true;
        backtrack(i + 1);
        col[j] = d1[i - j + 8] = d2[i + j - 1] = false;
    }
}

void solve() {
    FOR(i, 1, 8) {
        FOR(j, 1, 8) {
            char ch; cin >> ch;
            grid[i][j] = (ch == '*');
        }
    }

    backtrack(1);
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
