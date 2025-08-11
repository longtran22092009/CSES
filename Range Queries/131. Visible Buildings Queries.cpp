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


void solve() {
    int n, Q; cin >> n >> Q;
    
    vector <ll> a(n+1);
    FOR(i, 1, n) cin >> a[i];
    
    vector <int> nxt(n+1, 0), st;
    FORD(i, n, 1) { // Decreasing stack
        while (!st.empty() && a[st.back()] <= a[i]) st.pop_back();
        nxt[i] = (st.empty() ? -1 : st.back());
        st.push_back(i);
    }
    
    int LOG = 31;
    vector <vector <int>> up(n+1, vector <int>(LOG));

    FOR(i, 1, n) up[i][0] = nxt[i];
    FOR(j, 1, LOG-1) FOR(i, 1, n) {
        if (up[i][j-1] == -1) up[i][j] = -1;
        else up[i][j] = up[up[i][j-1]][j-1];
    }
    
    while (Q--) {
        int l, r; cin >> l >> r;
        int ans = 1, curr = l;

        FORD(k, LOG-1, 0) { // Try to go as far as possible
            int node = up[curr][k];
            if (node != -1 && node <= r) {
                curr = node;
                ans += MASK(k);
            }
        }

        cout << ans << endl;
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
