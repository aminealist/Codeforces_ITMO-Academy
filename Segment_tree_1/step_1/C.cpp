#pragma GCC optimize("unroll-loops", "unswitch-loops")
#pragma GCC optimize("Ofast", "no-stack-protector")
#pragma GCC optimize("profile-reorder-functions", "tracer")
#pragma GCC optimize("rename-registers", "vpt")
#pragma GCC optimize("fast-math")

#pragma GCC target("tune=native")

#include "bits/stdc++.h"

using namespace std;

#define ll long long

const ll INF = 1e12;

struct vertex {
    ll min = INF;
    ll count = 1;
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
        if (tree[2 * x + 1].min == tree[2 * x + 2].min) [[unlikely]] {
            tree[x].count = tree[2 * x + 1].count + tree[2 * x + 2].count;
        } else [[likely]] {
            tree[x].count =
                    tree[2 * x + 1].min < tree[2 * x + 2].min ? tree[2 * x + 1].count : tree[2 * x + 2].count;
        }
        tree[x].min = min(tree[2 * x + 1].min, tree[2 * x + 2].min);
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
            tree[x].min = v;
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

    vertex ask(ll l, ll r, ll x, ll lx, ll rx) {
        if (lx >= r || rx <= l) return {INF, 0};
        if (lx >= l && rx <= r) return tree[x];
        ll mid = (lx + rx) >> 1;
        vertex left = ask(l, r, 2 * x + 1, lx, mid);
        vertex right = ask(l, r, 2 * x + 2, mid, rx);
        if (left.min == right.min) [[unlikely]] {
            return {left.min, left.count + right.count};
        }
        return left.min < right.min ? left : right;
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
            vertex ans = a.ask(l, r, 0, 0, a.size);
            cout << ans.min << ' ' << ans.count << '\n';
        }
    }
}