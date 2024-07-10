#pragma GCC optimize("unroll-loops", "unswitch-loops")
#pragma GCC optimize("Ofast", "no-stack-protector")
#pragma GCC optimize("profile-reorder-functions", "tracer")
#pragma GCC optimize("rename-registers", "vpt")
#pragma GCC optimize("fast-math")

#pragma GCC target("tune=native")

#include "bits/stdc++.h"

using namespace std;

#define ll long long

struct vertex {
    ll x11 = 1, x12 = 0;
    ll x21 = 0, x22 = 1;
};


struct segtree {
    ll size;
    vector<vertex> tree;
    ll mod;

    void init(ll n, ll r) {
        size = 1;
        mod = r;
        while (size < n) size *= 2;
        tree.resize(2 * size - 1);
    }

    vertex product(vertex m1, vertex m2) {
        return {((m1.x11 * m2.x11) + (m1.x12 * m2.x21)) % mod,
                ((m1.x11 * m2.x12) + (m1.x12 * m2.x22)) % mod,
                ((m1.x21 * m2.x11) + (m1.x22 * m2.x21)) % mod,
                ((m1.x21 * m2.x12) + (m1.x22 * m2.x22)) % mod
        };
    }

    void build(ll x, ll lx, ll rx) {
        if (rx - lx != 1)[[likely]] {
            ll mx = (lx + rx) >> 1;
            build(2 * x + 1, lx, mx);
            build(2 * x + 2, mx, rx);
            tree[x] = product(tree[2 * x + 1], tree[2 * x + 2]);
        }
    }

    vertex ask(ll l, ll r, ll x, ll lx, ll rx) {
        if (lx >= r || rx <= l)
            return {1, 0,
                    0, 1};
        if (lx >= l && rx <= r) return tree[x];
        ll mx = (lx + rx) >> 1;
        return product(ask(l, r, 2 * x + 1, lx, mx), ask(l, r, 2 * x + 2, mx, rx));
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll rm, n, m;
    cin >> rm >> n >> m;
    segtree a;
    a.init(n, rm);
    for (ll i = 0; i < n; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        a.tree[a.size - 1 + i] = {x1, y1, x2, y2};
    }
    a.build(0, 0, a.size);
    while (m--) {
        ll l, r;
        cin >> l >> r;
        l--;
        vertex ans = a.ask(l, r, 0, 0, a.size);
        cout << ans.x11 << ' ' << ans.x12 << '\n' << ans.x21 << ' ' << ans.x22 << "\n\n";
    }
}