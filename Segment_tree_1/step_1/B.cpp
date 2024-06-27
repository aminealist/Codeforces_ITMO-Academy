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
    ll min = 1e15;
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
        if (rx - lx != 1) [[likely]] {
            ll mid = (lx + rx) >> 1;
            build(2 * x + 1, lx, mid);
            build(2 * x + 2, mid, rx);
            tree[x].min = min(tree[2 * x + 1].min, tree[2 * x + 2].min);
        }
    }

    void add(ll i, ll v, ll x, ll lx, ll rx) {
        if (rx - lx == 1) [[unlikely]] {
            tree[x].min = v;
        } else [[likely]] {
            ll mid = (lx + rx) >> 1;
            if (i < mid) {
                add(i, v, 2 * x + 1, lx, mid);
            } else {
                add(i, v, 2 * x + 2, mid, rx);
            }
            tree[x].min = min(tree[2 * x + 1].min, tree[2 * x + 2].min);
        }
    }

    ll ask(ll l, ll r, ll x, ll lx, ll rx) {
        if (lx >= r || rx <= l) return 1e15;
        if (lx >= l && rx <= r) return tree[x].min;
        ll mid = (lx + rx) >> 1;
        return min(ask(l, r, 2 * x + 1, lx, mid), ask(l, r, 2 * x + 2, mid, rx));
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
        cin >> a.tree[a.size - 1 + i].min;
    }
    a.build(0, 0, a.size);
    while (m--) {
        ll t;
        cin >> t;
        if (t == 1) {
            ll i, v;
            cin >> i >> v;
            a.add(i, v, 0, 0, a.size);
        } else {
            ll l, r;
            cin >> l >> r;
            cout << a.ask(l, r, 0, 0, a.size) << '\n';
        }
    }
}