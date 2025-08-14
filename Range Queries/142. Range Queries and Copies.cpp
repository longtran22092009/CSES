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

struct Node {
    ll sum;
    Node* left;
    Node* right;

    Node(ll _sum = 0, Node* _l = nullptr, Node* _r = nullptr) {
        sum = _sum;
        left = _l;
        right = _r;
    }
};

struct segtree {
    int n;
    segtree(int _n) : n(_n) {}

    Node* build(vector <ll> &a) {
        auto self = [&](auto&& self, int l, int r) -> Node* {
            if (r - l == 1) return new Node(a[l]);

            int mid = (l + r) / 2;
            Node* L = self(self, l, mid);
            Node* R = self(self, mid, r);
            return new Node(L->sum + R->sum, L, R);
        };
        return self(self, 1, n+1);
    }

    Node* update(Node* pre, int pos, ll val) {
        auto self = [&](auto&& self, Node* node, int pos, int val, int l, int r) -> Node* {
            if (r - l == 1) return new Node(val);

            int mid = (l + r) / 2;
            if (pos < mid) {
                Node* L = self(self, node->left, pos, val, l, mid);
                return new Node(L->sum + node->right->sum, L, node->right);
            }
            else {
                Node* R = self(self, node->right, pos, val, mid, r);
                return new Node(node->left->sum + R->sum, node->left, R);
            }
        };
        return self(self, pre, pos, val, 1, n+1);
    }

    ll query(Node* node, int ql, int qr) {
        auto self = [&](auto&& self, Node* node, int ql, int qr, int l, int r) -> ll {
            if (!node || qr <= l || ql >= r) return 0LL;
            if (ql <= l && r <= qr) return node->sum;

            int mid = (l + r) / 2;
            ll s1 = self(self, node->left, ql, qr, l, mid);
            ll s2 = self(self, node->right, ql, qr, mid, r);
            return s1 + s2;
        };
        return self(self, node, ql, qr, 1, n+1);
    }
};

void solve() {
    int n, Q; cin >> n >> Q;

    vector <ll> a(n+1);
    FOR(i, 1, n) cin >> a[i];

    segtree st(n);
    vector <Node*> version(2);
    version[1] = st.build(a);

    while (Q--) {
        int op, k; cin >> op >> k;

        if (op == 1) {
            int pos; cin >> pos;
            ll val; cin >> val;
            version[k] = st.update(version[k], pos, val);
        }
        else if (op == 2) {
            int l, r; cin >> l >> r;
            cout << st.query(version[k], l, r+1) << endl;
        }
        else version.push_back(version[k]);
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
