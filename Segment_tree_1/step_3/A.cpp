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

    void add(ll i, ll x, ll lx, ll rx) {
        if (rx - lx == 1) [[unlikely]] {
            tree[x].sum = 1;
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

    ll segSum(ll l, ll r, ll x, ll lx, ll rx) {
        if (lx >= r || rx <= l) return 0;
        if (lx >= l && rx <= r) return tree[x].sum;
        ll mx = (lx + rx) >> 1;
        return segSum(l, r, 2 * x + 1, lx, mx) + segSum(l, r, 2 * x + 2, mx, rx);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n;
    cin >> n;
    segtree a;
    a.init(n + 1);
    for (ll i = 0; i < n; i++) {
        ll v;
        cin >> v;
        cout << a.segSum(v, a.size, 0, 0, a.size) << ' ';
        a.add(v, 0, 0, a.size);
    }
}