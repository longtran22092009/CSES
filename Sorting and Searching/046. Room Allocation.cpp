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
const int mxN = 100005;

void solve() {
    int n; cin >> n;

    vector <array <int, 3>> events;
    vector <pair <int, int>> a(n);
    FOR(i, 0, n-1) {
        int l, r; cin >> l >> r;
        a[i] = {l, r};
        events.push_back({l, 0, i});
        events.push_back({r, 1, i});
    }
    sort(all(events));

    set <int> done; // room's id
    vector <int> ans(n);
    int currRoom = 0;

    for (auto &e : events) {
        int pos = e[0], id = e[2];
        if (e[1] == 0) {
            if (sz(done)) {
                int roomId = *done.begin();
                ans[id] = roomId;
                done.erase(done.begin());
            }
            else ans[id] = ++currRoom;
        }
        else done.insert(ans[id]);
    }

    cout << currRoom << endl;
    for (auto &x : ans) cout << x << " ";
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
