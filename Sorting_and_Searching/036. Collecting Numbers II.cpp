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
#define FOR(i, pos, b) for (int i = (pos); i <= (b); i++)
#define FORD(i, pos, b) for (int i = (pos); i >= (b); i--)
//====== FILE ======//
#define IN "A.in"
#define OUT "A.out"
#define DEBUG "debug.out"
//==================//

const int INF = (int) 1e9+5;
const ll LINF = (ll) 1e18;
const ll MOD = (ll) 1e9+7;
const int mxN = 100005;

void solve() {
    int n, m; cin >> n >> m;

    vector <int> pos(n+1, 0), val(n+1, 0);
    FOR(i, 1, n) {
        int x; cin >> x;
        pos[x] = i;
        val[i] = x;
    }
    
    int ans = 1;
    FOR(i, 2, n) if (pos[i] < pos[i-1]) ++ans;

    while (m--) {
        int a, b; cin >> a >> b;

        set <pair <ll, ll>> st;
        if (val[a]+1 <= n) st.insert({val[a], val[a]+1});
        if (val[a]-1 >= 1) st.insert({val[a]-1, val[a]});
        if (val[b]+1 <= n) st.insert({val[b], val[b]+1});
        if (val[b]-1 >= 1) st.insert({val[b]-1, val[b]});

        for (auto &x : st) if (pos[x.fi] > pos[x.se]) --ans;
        swap(pos[val[a]], pos[val[b]]);
        swap(val[a], val[b]);
        for (auto &x : st) if (pos[x.fi] > pos[x.se]) ++ans;

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
