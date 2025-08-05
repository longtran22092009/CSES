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

vector <int> dx = {-1, 1, 0, 0};
vector <int> dy = {0, 0, -1, 1};
string dir = "UDLR";
int n, m;
char grid[mxN][mxN];
bool vis[mxN][mxN];
pair <int, int> s, t;
int pre[mxN][mxN];

void bfs() {
    queue <pair <int, int>> q; q.push(s);
    vis[s.fi][s.se] = true;

    while (!q.empty()) {
        int x = q.front().fi, y = q.front().se;
        q.pop();

        FOR(i, 0, 3) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            if (vis[nx][ny] || grid[nx][ny] == '#') continue;

            vis[nx][ny] = true;
            pre[nx][ny] = i;
            q.push({nx, ny});
        }
    }
}

void solve() {
    cin >> n >> m;
    FOR(i, 1, n) FOR(j, 1, m) {
        cin >> grid[i][j];
        if (grid[i][j] == 'A') s = {i, j};
        else if (grid[i][j] == 'B') t = {i, j};
    }

    bfs();

    if (!vis[t.fi][t.se]) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    string ans = "";
    while (t != s) {
        int d = pre[t.fi][t.se];
        t.fi -= dx[d], t.se -= dy[d];
        ans += dir[d];
    }

    cout << sz(ans) << endl;
    reverse(all(ans));
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
 