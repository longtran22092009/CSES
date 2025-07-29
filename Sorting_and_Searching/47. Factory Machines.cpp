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
//====== FILE ======//
#define IN "A.in"
#define OUT "A.out"
#define DEBUG "debug.out"
//==================//
 
const int INF = (int) 1e9+5;
const ll LINF = (ll) 1e18;
const ll MOD = (ll) 1e9+7;
const int mxN = 200005;
 
ll n, t;
vector <ll> a(mxN);
 
bool check(ll time) {
    ll res = 0;
    FOR(i, 0, n-1) {
        res += time / a[i];
        if (res >= t) return true;
    }
    return false;
}
 
void solve() {
    cin >> n >> t;
    FOR(i, 0, n-1) cin >> a[i];
 
    ll l = 1, r = LINF, ans = LINF;
    while (l <= r) {
        ll mid = (l + r) / 2;
 
        if (check(mid)) {
            ans = mid;
            r = mid-1;
        }
        else l = mid+1;
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