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
const int mxN = 1005;

int n;
int grid[mxN][mxN];
vector <int> dx = {-2, -2, -1, 1, -1, 1, 2, 2};
vector <int> dy = {-1, 1, -2, -2, 2, 2, -1, 1};

void bfs() {
    queue <pair <int, int>> q; 
    q.push({1, 1}); // {x, y, dis}
    grid[1][1] = 0;

    while (!q.empty()) {
        pair <int, int> a = q.front(); q.pop();
        
        FOR(i, 0, 7) {
            int nx = a.fi + dx[i], ny = a.se + dy[i];
            if (nx < 1 || nx > n || ny < 1 || ny > n || grid[nx][ny] != -1) continue;
            q.push({nx, ny});
            grid[nx][ny] = grid[a.fi][a.se] + 1;
        }
    }
}

void solve() {
    cin >> n;

    memset(grid, -1, sizeof(grid));
    bfs();

    FOR(i, 1, n) {
        FOR(j, 1, n) cout << grid[i][j] << " ";
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
