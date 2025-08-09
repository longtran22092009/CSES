#include <bits/stdc++.h>
using namespace std;
//====== BITWISE ======//
#define MASK(i) (1LL << (i))
#define BIT(x, i) (((x) >> (i)) & 1)
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

// Warnsdorff's Rule
const int INF = (int) 1e9+5;
const ll LINF = (ll) 1e18;
const ll MOD = (ll) 1e9+7;
const int mxN = 8;

vector <int> dx = {-2, -2, 2, 2, -1, 1, -1, 1};
vector <int> dy = {-1, 1, -1, 1, -2, -2, 2, 2};
int a[mxN+1][mxN+1];

bool isBlocked(int x, int y) {
    return (x < 1 || x > mxN || y < 1 || y > mxN || a[x][y]);
}

int calculateEmptyCells(int x, int y) {
    int res = 0;
    FOR(i, 0, 7) {
        int nx = x + dx[i], ny = y + dy[i];
        if (!isBlocked(nx, ny)) ++res;
    }
    return res;
}

bool dfs(int x, int y, int step) {
    a[x][y] = step;
    if (step == 64) return true;

    vector <array <int, 3>> choice;
    FOR(i, 0, 7) {
        int nx = x + dx[i], ny = y + dy[i];
        if (!isBlocked(nx, ny)) {
            int emptyCells = calculateEmptyCells(nx, ny);
            choice.push_back({emptyCells, nx, ny});
        }
    }

    // Choose the cell with less empty to-cells first
    sort(all(choice)); 
    for (auto &cell : choice)
        if (dfs(cell[1], cell[2], step+1)) return true;
    
    a[x][y] = 0;
    return false;
}

void solve() {
    int x, y; cin >> y >> x;
    dfs(x, y, 1);

    FOR(i, 1, mxN) {
        FOR(j, 1, mxN) cout << a[i][j] << " ";
        cout << endl;
    }
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
