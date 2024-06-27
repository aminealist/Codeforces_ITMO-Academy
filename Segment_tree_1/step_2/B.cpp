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
        if (rx - lx != 1) [[likely]] {
            ll mid = (lx + rx) >> 1;
            build(2 * x + 1, lx, mid);
            build(2 * x + 2, mid, rx);
            tree[x].sum = tree[2 * x + 1].sum + tree[2 * x + 2].sum;
        }
    }

    void add(ll i, ll x, ll lx, ll rx) {
        if (rx - lx == 1) [[unlikely]] {
            tree[x].sum = 1 - tree[x].sum;
        } else [[likely]] {
            ll mid = (lx + rx) >> 1;
            if (i < mid) {
                add(i, 2 * x + 1, lx, mid);
            } else {
                add(i, 2 * x + 2, mid, rx);
            }
            tree[x].sum = tree[2 * x + 1].sum + tree[2 * x + 2].sum;
        }
    }

    ll ask(ll k, ll x, ll lx, ll rx) {
        if (rx - lx == 1) {
            return lx;
        }
        ll mid = (lx + rx) >> 1;
        if (tree[2 * x + 1].sum >= k) {
            return ask(k, 2 * x + 1, lx, mid);
        } else {
            return ask(k - tree[2 * x + 1].sum, 2 * x + 2, mid, rx);
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
        cin >> a.tree[a.size - 1 + i].sum;
    }
    a.build(0, 0, a.size);
    while (m--) {
        ll t;
        cin >> t;
        if (t == 1) {
            ll i;
            cin >> i;
            a.add(i, 0, 0, a.size);
        } else {
            ll k;
            cin >> k;
            cout << a.ask(k + 1, 0, 0, a.size) << '\n';
        }
    }
}