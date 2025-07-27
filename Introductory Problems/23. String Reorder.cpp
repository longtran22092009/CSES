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
#define FORE(a, b) for (auto a : b)
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
    string s; cin >> s;
    int n = sz(s);

    vector <int> f(26, 0);
    FORE(&ch, s) f[ch - 'A']++;
    if (*max_element(all(f)) > (n+1) / 2) {
        cout << "-1\n";
        return;
    }

    string ans = "";
    char lst = '?';
    FOR(i, 0, n-1) {
        bool ok = false;

        FOR(c, 0, 25) {
            char ch = c + 'A';
            if (f[c] == 0 || lst == ch) continue;

            --f[c];
            if (*max_element(all(f)) <= ((n-i) / 2)) { // ceil((n-i-2) / 2)
                ans += ch;
                lst = ch;
                ok = true;
                break;
            }
            else ++f[c];
        }

        if (!ok) {
            cout << "-1\n";
            return;
        }
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
