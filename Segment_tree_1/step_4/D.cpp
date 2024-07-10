#pragma GCC optimize("unroll-loops", "unswitch-loops")
#pragma GCC optimize("Ofast", "no-stack-protector")
#pragma GCC optimize("profile-reorder-functions", "tracer")
#pragma GCC optimize("rename-registers", "vpt")
#pragma GCC optimize("fast-math")

#pragma GCC target("tune=native")

#include "bits/stdc++.h"

using namespace std;

#define ll long long


struct segtree {
    ll size;
    vector<ll> tree;

    void init(ll n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size - 1, 0);
    }

    void build(ll x, ll lx, ll rx) {
        if (rx - lx != 1)[[likely]] {
            ll mx = (lx + rx) >> 1;
            build(2 * x + 1, lx, mx);
            build(2 * x + 2, mx, rx);
            tree[x] = tree[2 * x + 1] | tree[2 * x + 2];
        }
    }

    void add(ll next, ll i, ll x, ll lx, ll rx) {
        if (rx - lx == 1)[[unlikely]] {
            tree[x] = 1ll << next;
        } else [[likely]] {
            ll mx = (lx + rx) >> 1;
            if (i < mx) {
                add(next, i, 2 * x + 1, lx, mx);
            } else {
                add(next, i, 2 * x + 2, mx, rx);
            }
            tree[x] = tree[2 * x + 1] | tree[2 * x + 2];
        }
    }

    ll ask(ll l, ll r, ll x, ll lx, ll rx) {
        if (lx >= r || rx <= l) return 0;
        if (lx >= l && rx <= r)return tree[x];
        ll mx = (lx + rx) >> 1;
        return ask(l, r, 2 * x + 1, lx, mx) | ask(l, r, 2 * x + 2, mx, rx);
    }


};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, m;
    cin >> n >> m;
    segtree a;
    a.init(n);
    for (ll i = 0; i < n; i++) {
        ll el;
        cin >> el;
        a.tree[a.size - 1 + i] = 1ll << el;
    }
    a.build(0, 0, a.size);
    while (m--) {
        ll t, x, y;
        cin >> t >> x >> y;
        x--;
        if (t == 1) cout << __builtin_popcountll(a.ask(x, y, 0, 0, a.size)) << '\n';
        else a.add(y, x, 0, 0, a.size);

    }
}
