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
    ll sum;
    ll prefSum;
    ll sufSum;
    ll midSum;
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
        tree[x].sum = tree[2 * x + 1].sum + tree[2 * x + 2].sum;
        tree[x].prefSum = max(0ll, tree[2 * x + 1].prefSum);
        tree[x].prefSum = max(tree[x].prefSum, tree[2 * x + 1].sum + tree[2 * x + 2].prefSum);
        tree[x].sufSum = max(0ll, tree[2 * x + 2].sufSum);
        tree[x].sufSum = max(tree[x].sufSum, tree[2 * x + 2].sum + tree[2 * x + 1].sufSum);
        tree[x].midSum = max(tree[2 * x + 1].midSum, tree[2 * x + 2].midSum);
        tree[x].midSum = max(tree[x].midSum, tree[2 * x + 1].sufSum + tree[2 * x + 2].prefSum);
    }

    void build(ll x, ll lx, ll rx) {
        if (rx - lx == 1) [[unlikely]] {
            tree[x].midSum = tree[x].sufSum = tree[x].prefSum = max(0ll, tree[x].sum);
        } else [[likely]] {
            ll mid = (lx + rx) >> 1;
            build(2 * x + 1, lx, mid);
            build(2 * x + 2, mid, rx);
            relax(x);
        }
    }


    void add(ll i, ll v, ll x, ll lx, ll rx) {
        if (rx - lx == 1) [[unlikely]] {
            tree[x].sum = v;
            tree[x].midSum = tree[x].sufSum = tree[x].prefSum = max(0ll, tree[x].sum);
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

    ll ask() {
        return max(max(tree[0].sum, tree[0].midSum), max(tree[0].prefSum, tree[0].sufSum));
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
        cin >> a.tree[a.size - 1 + i].sum;
    }
    a.build(0, 0, a.size);
    cout << a.ask() << '\n';
    while (m--) {
        ll i, v;
        cin >> i >> v;
        a.add(i, v, 0, 0, a.size);
        cout << a.ask() << '\n';
    }
}