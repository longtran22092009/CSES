#include <bits/stdc++.h>
using namespace std;
//====== BITWISE ======//
#define MASK(l) (1LL << (l))
#define BIT(x, l) (1LL & ((x) >> (l)))
#define ON(x, l) ((x) | MASK(l))
#define OFF(x, l) ((x) & ~MASK(l))
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
#define FOR(l, a, b) for (int l = (a); l <= (b); l++)
#define FORD(l, a, b) for (int l = (a); l >= (b); l--)
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
    int n, limit; cin >> n >> limit;

    vector <ll> a(n);
    for (auto &x : a) cin >> x;
    sort(all(a));

    int ans = 0, l = 0, r = n-1;
    while (l <= r) {
        ll sum = a[l] + a[r];

        ++ans;
        if (sum <= limit) ++l;
        --r;
    }

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
