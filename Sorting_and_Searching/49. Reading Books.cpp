#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define Longgggg ios_base::sync_with_stdio(0); cin.tie(0);
#define IN "A.in"
#define OUT "A.out"
#define DEBUG "debug.out"

void solve() {
    int n; cin >> n;
    vector<ll> a(n);
    ll sum = 0, mx = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
        mx = max(mx, a[i]);
    }

    /**
     *  Neu co the chia deu thoi gian cho 2 de doc thi moi nguoi chi can sum/2 de doc het
     *  Nguoc lai thi neu co mot cuon sach co thoi gian qua lon, phai doc rieng cuon do
     *  thi tong thoi gian de 2 nguoi do chet la mx*2 voi mx la thoi gain lon nhat phai doc
    **/
    cout << max(sum, 2 * mx) << '\n';
}

int main() {
    if (fopen(IN, "r")) {
        freopen(IN, "r", stdin);
        freopen(OUT, "w", stdout);
        freopen(DEBUG, "w", stderr);
    }
    Longgggg
    solve();
    return 0;
}
