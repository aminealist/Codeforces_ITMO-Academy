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

    void add(ll l, ll r, ll v, ll x, ll lx, ll rx) {
        if (lx >= r || rx <= l) [[unlikely]] return;
        if (lx >= l && rx <= r)[[likely]] {
            tree[x].sum += v;
            return;
        }
        ll mid = (lx + rx) >> 1;
        add(l, r, v, 2 * x + 1, lx, mid);
        add(l, r, v, 2 * x + 2, mid, rx);
    }

    ll ask(ll i, ll x, ll lx, ll rx) {
        if (rx - lx == 1) [[unlikely]] {
            return tree[x].sum;
        }
        ll mx = (lx + rx) >> 1;
        ll p = 0;
        if (i < mx) {
            p = ask(i, 2 * x + 1, lx, mx);
        } else {
            p = ask(i, 2 * x + 2, mx, rx);
        }
        return p + tree[x].sum;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, m;
    cin >> n >> m;
    segtree a;
    a.init(n);
    while (m--) {
        ll t;
        cin >> t;
        if (t == 1) {
            ll l, r, v;
            cin >> l >> r >> v;
            a.add(l, r, v, 0, 0, a.size);
        } else {
            ll i;
            cin >> i;
            cout << a.ask(i, 0, 0, a.size) << '\n';
        }
    }
}