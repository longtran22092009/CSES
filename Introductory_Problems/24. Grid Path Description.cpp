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
#define FORE(a, b) for (auto a : b)
//====== FILE ======//
#define IN "A.in"
#define OUT "A.out"
#define DEBUG "debug.out"
//==================//

const int INF = (int) 1e9+5;
const ll LINF = (ll) 1e18;
const ll MOD = (ll) 1e9+7;
const int mxN = 10;

vector <char> dir = {'U', 'D', 'L', 'R'};
vector <int> dx = {-1, 1, 0, 0};
vector <int> dy = {0, 0, -1, 1};
string s;
int ans = 0;
bool vis[mxN][mxN];

bool isBlocked(int x, int y) {
    return (x < 1 || x > 7 || y < 1 || y > 7 || vis[x][y]);
}

void dfs(int x, int y, int step) {
    // Wrong location?
    if (step == 48) {
        if (x == 7 && y == 1) ++ans;
        return;
    }
    // Wrong path?
    if (x == 7 && y == 1) return;
    // Split the grid (next to an edge)?
    if (isBlocked(x-1, y) && isBlocked(x+1, y) && !isBlocked(x, y-1) && !isBlocked(x, y+1)) return;
    if (!isBlocked(x-1, y) && !isBlocked(x+1, y) && isBlocked(x, y-1) && isBlocked(x, y+1)) return;

    vis[x][y] = true;
    FOR(i, 0, 3) {
        if (s[step] != '?' && s[step] != dir[i]) continue;

        int nx = x + dx[i], ny = y + dy[i];
        if (!isBlocked(nx, ny)) dfs(nx, ny, step + 1);
    }
    vis[x][y] = false;
}

void solve() {
    cin >> s;

    dfs(1, 1, 0);
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
