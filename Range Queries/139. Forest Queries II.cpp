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

const int INF = (int) 1e9+5;
const ll LINF = (ll) 1e18;
const ll MOD = (ll) 1e9+7;
const int mxN = 100005;

struct Fenwick {
    int n;
    vector <vector <int>> bit;

    Fenwick(int _n) {
        n = _n;
        bit.assign(n+1, vector <int> (n+1, 0));
    }

    void update(int row, int col, int val) {
        for (int i = row; i <= n; i += LASTBIT(i))
            for (int j = col; j <= n; j += LASTBIT(j))
                bit[i][j] += val;
    }

    int query(int row, int col) {
        int sum = 0;
        for (int i = row; i > 0; i -= LASTBIT(i))
            for (int j = col; j > 0; j -= LASTBIT(j))
                sum += bit[i][j];
        return sum;
    }
};

void solve() {
    int n, Q; cin >> n >> Q;

    Fenwick bit(n);
    vector <vector <int>> grid(n+1, vector <int>(n+1, 0));
    FOR(i, 1, n) FOR(j, 1, n) {
        char ch; cin >> ch;
        grid[i][j] = (ch == '*');
        bit.update(i, j, grid[i][j]);
    }

    while (Q--) {
        int op; cin >> op;

        if (op == 1) {
            int r, c; cin >> r >> c;
            bit.update(r, c, (grid[r][c] == 1 ? -1 : 1));
            grid[r][c] ^= 1;
        }
        else {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;
            int ans = bit.query(r2, c2) - bit.query(r1-1, c2) - bit.query(r2, c1-1);
            ans += bit.query(r1-1, c1-1);
            cout << ans << endl;
        }
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
