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
    vector <int> bit;

    Fenwick(int _n) {
        n = _n;
        bit.assign(n + 1, 0);
    }

    void update(int idx, int val) {
        for (; idx <= n; idx += LASTBIT(idx))
            bit[idx] += val;
    }

    int query(int idx) {
        int sum = 0;
        for (; idx > 0; idx -= LASTBIT(idx))
            sum += bit[idx];
        return sum;
    }

    int range_query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l-1);
    }
};

void solve() {
    int n, Q; cin >> n >> Q;

    vector <int> a(n+1), coords;
    FOR(i, 1, n) {
        cin >> a[i];
        coords.push_back(a[i]);
    }
    
    vector <array <int, 3>> queries;
    FOR(i, 1, Q) {
        char op; cin >> op;
        int a, b; cin >> a >> b;
        queries.push_back({(op == '!' ? 1 : 2), a, b});
        if (op == '!') coords.push_back(b);
    }

    compress(coords);
    auto getId = [&](int x) -> int {
        int pos = lower_bound(all(coords), x) - coords.begin() + 1;
        return pos;
    };

    Fenwick bit(sz(coords));
    FOR(i, 1, n) bit.update(getId(a[i]), 1);

    for (auto &q : queries) {
        int op = q[0];
        
        if (op == 1) {
            int k = q[1], x = q[2];
            bit.update(getId(a[k]), -1);
            bit.update(getId(x), 1);
            a[k] = x;
        }
        else {
            int a = q[1], b = q[2];
            int l = getId(a); // First element >= L
            int r = upper_bound(all(coords), b) - coords.begin(); // Last element <= R
            cout << bit.range_query(l, r) << endl;
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
