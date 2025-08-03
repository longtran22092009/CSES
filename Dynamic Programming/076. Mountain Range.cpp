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
const int mxN = 200005;

vector <int> dp(mxN, 0), lower[mxN];
vector <pair <int, int>> st; // {val, id}

// Find the best way to go for each position
int dfs(int u) { 
    if (dp[u]) return dp[u];
    for (auto &v : lower[u]) dp[u] = max(dp[u], dfs(v) + 1);
    return dp[u];
}

void solve() {
    int n; cin >> n;

    vector <int> a(n);
    for (auto &x : a) cin >> x;

    // All moutains that can go to on the right of moutain i
    FOR(i, 0, n-1) {
        while (!st.empty() && st.back().fi < a[i]) {
            lower[i].push_back(st.back().se);
            st.pop_back();
        }
        st.push_back({a[i], i});
    }
    
    st.clear();
    // All moutains that can go to on the left of moutain i
    FORD(i, n-1, 0) {
        while (!st.empty() && st.back().fi < a[i]) {
            lower[i].push_back(st.back().se);
            st.pop_back();
        }
        st.push_back({a[i], i});
    }

    int ans = -1;
    FOR(i, 0, n-1) ans = max(ans, dfs(i) + 1);
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
