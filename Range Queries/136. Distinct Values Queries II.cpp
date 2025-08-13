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

map <int, set <int>> nxt;

int getNextPos(int idx, int val) {
    auto it = nxt[val].upper_bound(idx);
   return (it == nxt[val].end() ? INF : *it);
}

int getPrevPos(int idx, int val) {
    auto it = nxt[val].lower_bound(idx);
   return (it == nxt[val].begin() ? 0 : *(--it));
}

// Tree node v represents [l, r)
struct segtree {
    int N;
    vector <int> tree;
    
    segtree(int n) {
        N = n;
        tree.assign(4 * N, INF);
    }


    void build(vector <int> &a) {
        auto self = [&](auto&& self, int v, int l, int r) -> void {
            if (r - l == 1) {
                tree[v] = a[l];
                return;
            }

            int mid = (l + r) / 2;
            self(self, 2 * v, l, mid);
            self(self, 2 * v + 1, mid, r);
            tree[v] = min(tree[2 * v], tree[2 * v + 1]);
        };
        self(self, 1, 1, N+1);
    }

    void update(int pos, int val) {
        auto self = [&](auto&& self, int pos, int val, int v, int l, int r) -> void {
            if (r - l == 1) {
                tree[v] = val;
                return;
            }
 
            int mid = (l + r) / 2;
            if (pos < mid) self(self, pos, val, 2 * v, l, mid);
            else self(self, pos, val, 2 * v + 1, mid, r);
            tree[v] = min(tree[2 * v], tree[2 * v + 1]);
        };
        self(self, pos, val, 1, 1, N+1);
    }

    int query(int ql, int qr) {
        auto self = [&](auto&& self, int ql, int qr, int v, int l, int r) -> int {
            if (qr <= l || ql >= r) return INF;
            if (ql <= l && r <= qr) return tree[v];

            int mid = (l + r) / 2;
            int s1 = self(self, ql, qr, 2 * v, l, mid);
            int s2 = self(self, ql, qr, 2 * v + 1, mid, r);
            return min(s1, s2);
        };
        return self(self, ql, qr, 1, 1, N+1);
    }
};

void solve() {
    int n, Q; cin >> n >> Q;

    vector <int> a(n+1);
    FOR(i, 1, n) {
        cin >> a[i];
        nxt[a[i]].insert(i);
    }

    vector<int> nxtPos(n+1, INF);
    for (auto &x : nxt) {
        int prev = 0;
        for (int idx : x.second) {
            if (prev) nxtPos[prev] = idx;
            prev = idx;
        }
    }

    segtree st(n);
    st.build(nxtPos);

    while (Q--) {
        int op; cin >> op;       

        if (op == 1) {
            int k, x; cin >> k >> x;

            int oldVal = a[k], oldPrev = 0, oldNext = INF;
            auto it = nxt[oldVal].find(k);
            if (it != nxt[oldVal].begin()) oldPrev = *prev(it);
            if (next(it) != nxt[oldVal].end()) oldNext = *next(it);

            // Remove k in oldVal
            nxt[oldVal].erase(it);
            if (oldPrev) {
                nxtPos[oldPrev] = oldNext;
                st.update(oldPrev, nxtPos[oldPrev]);
            }

            nxt[x].insert(k);
            int newPrev = 0, newNext = INF;
            it = nxt[x].find(k); 
            if (it != nxt[x].begin()) newPrev = *prev(it);
            if (next(it) != nxt[x].end()) newNext = *next(it);

            nxtPos[k] = newNext;       
            st.update(k, nxtPos[k]);
            if (newPrev) {
                nxtPos[newPrev] = k;   
                st.update(newPrev, nxtPos[newPrev]);
            }

            a[k] = x;
        }
        else {
            int l, r; cin >> l >> r;
            int mnId = st.query(l, r+1);
            cout << (mnId > r ? "YES\n" : "NO\n");
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
