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
    ll max = 0;
};


struct segtree {
    ll size;
    vector<vertex> tree;

    void init(ll n) {
        size = 1;
        while (size < n) size *= 2;
        tree.resize(2 * size - 1);
    }

    void relax(ll x) {
        tree[x].max = max(tree[2 * x + 1].max, tree[2 * x + 2].max);
    }

    void build(ll x, ll lx, ll rx) {
        if (rx - lx != 1) [[likely]] {
            ll mid = (lx + rx) >> 1;
            build(2 * x + 1, lx, mid);
            build(2 * x + 2, mid, rx);
            relax(x);
        }
    }

    void add(ll i, ll v, ll x, ll lx, ll rx) {
        if (rx - lx == 1) [[unlikely]] {
            tree[x].max = v;
        } else [[likely]] {
            ll mid = (lx + rx) >> 1;
            if (i < mid) {
                add(i, v, 2 * x + 1, lx, mid);
            } else {
                add(i, v, 2 * x + 2, mid, rx);
            }
            relax(x);
        }
    }

    ll maximum(ll l, ll r, ll x, ll lx, ll rx) {
        if (lx >= r || rx <= l) return -1;
        if (lx >= l && rx <= r) return tree[x].max;
        ll mid = (lx + rx) >> 1;
        return max(maximum(l, r, 2 * x + 1, lx, mid), maximum(l, r, 2 * x + 2, mid, rx));
    }

    ll ask(ll l, ll v, ll x, ll lx, ll rx) {
        if (tree[x].max < v) return -1;
        if (rx - lx == 1) return lx;
        ll mid = (lx + rx) >> 1;
        if (maximum(l, mid, 2 * x + 1, lx, mid) >= v) {
            return ask(l, v, 2 * x + 1, lx, mid);
        } else {
            return ask(l, v, 2 * x + 2, mid, rx);
        }
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
        cin >> a.tree[a.size - 1 + i].max;
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
            ll l, v;
            cin >> v >> l;
            cout << a.ask(l, v, 0, 0, a.size) << '\n';
        }
    }
}