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
    ll sum = 0;
};


struct segtree {
    ll size;
    vector<vertex> tree;

    void init(ll n) {
        size = 1;
        while (size < n) size *= 2;
        tree.resize(2 * size - 1);
    }

    void build(ll x, ll lx, ll rx) {
        if (rx - lx != 1)[[likely]] {
            ll mx = (lx + rx) >> 1;
            build(2 * x + 1, lx, mx);
            build(2 * x + 2, mx, rx);
            tree[x].sum = tree[2 * x + 1].sum + tree[2 * x + 2].sum;
        }
    }

    void add(ll i, ll v, ll x, ll lx, ll rx) {
        if (rx - lx == 1)[[unlikely]] {
            tree[x].sum = v;
        } else[[likely]] {
            ll mx = (lx + rx) >> 1;
            if (i < mx) {
                add(i, v, 2 * x + 1, lx, mx);
            } else {
                add(i, v, 2 * x + 2, mx, rx);
            }
            tree[x].sum = tree[2 * x + 1].sum + tree[2 * x + 2].sum;
        }
    }

    ll ask(ll l, ll r, ll x, ll lx, ll rx) {
        if (lx >= r || rx <= l) return 0;
        if (lx >= l && rx <= r) return tree[x].sum;
        ll mx = (lx + rx) >> 1;
        return ask(l, r, 2 * x + 1, lx, mx) + ask(l, r, 2 * x + 2, mx, rx);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, m;
    cin >> n;
    segtree a;
    a.init(n);
    for (ll i = 0; i < n; i++) {
        cin >> a.tree[a.size - 1 + i].sum;
        a.tree[a.size - 1 + i].sum *= i & 1 ? -1 : 1;
    }
    a.build(0, 0, a.size);
    cin >> m;
    while (m--) {
        ll t;
        cin >> t;
        if (t) {
            ll l, r;
            cin >> l >> r;
            l--;
            cout << (l & 1 ? -1 : 1) * a.ask(l, r, 0, 0, a.size) << '\n';
        } else {
            ll i, v;
            cin >> i >> v;
            i--;
            a.add(i, v * (i & 1 ? -1 : 1), 0, 0, a.size);
        }
    }
}