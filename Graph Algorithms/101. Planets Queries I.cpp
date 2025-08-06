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
const int mxN = 200005;
 
const int LOG = 31;
int n, Q;
int up[mxN][LOG];
 
int getAncestor(int node, ll k) {
    FOR(j, 0, LOG - 1) if (BIT(k, j)) 
        node = up[node][j];
    return node;
}
 
void solve() {
    cin >> n >> Q;
    FOR(i, 1, n) cin >> up[i][0];
    // x: up[i][0], from i to x -> from x to i
    // we do this for binary lifting
    
    // Binary Lifting
    FOR(j, 1, LOG - 1) FOR(i, 1, n)
        up[i][j] = up[ up[i][j - 1] ][j - 1];
 
    while (Q--) {
        int u; cin >> u;
        ll k; cin >> k;
        cout << getAncestor(u, k) << endl;
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
