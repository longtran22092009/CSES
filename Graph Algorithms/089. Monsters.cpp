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
int pre[mxN][mxN];

pair <int, int> A;
vector <pair <int, int>> M;
int disA[mxN][mxN];
int disM[mxN][mxN];

// Find the shortest path from any monster to each cell
void bfsMonsters() {
    queue <pair <int, int>> q;
    for (auto &mons : M) {
        vis[mons.fi][mons.se] = true;
        disM[mons.fi][mons.se] = 0;
        q.push(mons);
    }

    while (!q.empty()) {
        int x = q.front().fi, y = q.front().se;
        q.pop();

        FOR(i, 0, 3) {
            int nx = x + dx[i], ny = y + dy[i];

            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            if (vis[nx][ny] || grid[nx][ny] == '#') continue;
            
            vis[nx][ny] = true;
            disM[nx][ny] = disM[x][y] + 1;
            q.push({nx, ny});
        }
    }
}

// Find the shortest path from A to each cell
void findPath() {
    queue <pair <int, int>> q;
    vis[A.fi][A.se] = true;
    disA[A.fi][A.se] = 0;
    q.push(A);
    
    while (!q.empty()) {
        int x = q.front().fi, y = q.front().se;
        q.pop();
        
        // Found the path to exit
        if (x == 1 || x == n || y == 1 || y == m) {
            string path = "";
            pair <int, int> s = {x, y};
            while (s != A) {
                int id = pre[s.fi][s.se];
                path.push_back(dir[id]);
                s.fi -= dx[id], s.se -= dy[id];
            }
            
            cout << "YES\n" << sz(path) << endl;
            reverse(all(path));
            cout << path << endl;
            return;
        }
        
        FOR(i, 0, 3) {
            int nx = x + dx[i], ny = y + dy[i];
            
            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            if (vis[nx][ny] || grid[nx][ny] == '#') continue;
            // The monsters can reach this cell before A
            if (disA[x][y] + 1 >= disM[nx][ny]) continue;
            
            vis[nx][ny] = true;
            disA[nx][ny] = disA[x][y] + 1;
            pre[nx][ny] = i;
            q.push({nx, ny});
        }
    }
    
    cout << "NO\n";
}

void solve() {
    cin >> n >> m;
    FOR(i, 1, n) FOR(j, 1, m) {
        cin >> grid[i][j];
        if (grid[i][j] == 'A') A = {i, j};
        if (grid[i][j] == 'M') M.push_back({i, j});
    }
    
    fill(&disA[0][0], &disA[0][0] + mxN * mxN, INF);
    fill(&disB[0][0], &disB[0][0] + mxN * mxN, INF);
    bfsMonsters();

    memset(vis, false, sizeof(vis));
    findPath();
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
