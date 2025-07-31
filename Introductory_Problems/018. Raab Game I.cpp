#include <bits/stdc++.h>
using namespace std;
//====== BITWISE ======//
#define MASK(i) (1LL << (i))
#define BIT(a, i) (1LL & ((a) >> (i)))
#define ON(a, i) ((a) | MASK(i))
#define OFF(a, i) ((a) & ~MASK(i))
#define LASTBIT(mask) ((mask) & -(mask))
#define SUBMASK(sub, mask) for (int sub = (mask); sub >= 1; sub = (sub - 1) & (mask))
//====== OTHER ======//
#define fi first
#define se second
#define ll long long
#define endl '\n'
#define sz(a) (int)size(a)
#define all(a) begin(a), end(a)
#define mod(a, k) ((((a) % (k)) + (k)) % (k))
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
const int mxN = 100005;

void solve() {
    int n, a, b; cin >> n >> a >> b;

    if (a == 0 && b == 0) {
        cout << "YES\n"   ;
        FOR(i, 1, 2) {
            FOR(j, 1, n) cout << j << " ";
            cout << endl;
        }
        return;
    }

    if (a + b > n || a == 0 || b == 0) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    int ties = n - a - b;
    FOR(i, 1, n) cout << i << " ";
    cout << endl;

    FOR(i, 1, ties) cout << i << " ";
    FOR(i, n-b+1, n) cout << i << " ";
    FOR(i, ties+1, n-b) cout << i << " ";
    cout << endl;
}

signed main() {
    if (fopen(IN, "r")) {
        freopen(IN, "r", stdin);
        freopen(OUT, "w", stdout);
        freopen(DEBUG, "w", stderr);
    }
    Longgggg

    ll t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}
