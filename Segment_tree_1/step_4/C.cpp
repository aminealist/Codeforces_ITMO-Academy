#pragma GCC optimize("unroll-loops", "unswitch-loops")
#pragma GCC optimize("Ofast", "no-stack-protector")
#pragma GCC optimize("profile-reorder-functions", "tracer")
#pragma GCC optimize("rename-registers", "vpt")
#pragma GCC optimize("fast-math")

#pragma GCC target("tune=native")

#include "bits/stdc++.h"

using namespace std;

#define ll long long
const ll maxa = 45;
const vector<ll> empty(maxa, 0);

struct vertex {
    vector<ll> v = empty;
    ll k = 0;
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
        tree[x].k = tree[2 * x + 1].k + tree[2 * x + 2].k;
        ll s = 0;
        for (ll i = 0; i < maxa; i++) {
            tree[x].v[i] = tree[2 * x + 1].v[i] + tree[2 * x + 2].v[i];
            tree[x].k += tree[2 * x + 1].v[i] * s;
            s += tree[2 * x + 2].v[i];
        }
    }

    void build(ll x, ll lx, ll rx) {
        if (rx - lx != 1) [[likely]] {
            ll mx = (lx + rx) >> 1;
            build(2 * x + 1, lx, mx);
            build(2 * x + 2, mx, rx);
            relax(x);
        }
    }

    void add(ll i, ll v, ll x, ll lx, ll rx) {
        if (rx - lx == 1) [[unlikely]] {
            tree[x].v = empty;
            tree[x].v[v] = 1;
        } else [[likely]] {
            ll mx = (lx + rx) >> 1;
            if (i < mx) {
                add(i, v, 2 * x + 1, lx, mx);
            } else {
                add(i, v, 2 * x + 2, mx, rx);
            }
            relax(x);
        }
    }

    ll ask(ll l, ll r, ll x, ll lx, ll rx) {
        if (lx >= r || rx <= l) return 0;
        if (lx >= l && rx <= r) return tree[x].k;
        ll mx = (lx + rx) >> 1;
        return ask(l, r, 2 * x + 1, lx, mx) + ask(l, r, 2 * x + 2, mx, rx);
    }

};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, q;
    cin >> n >> q;
    segtree a;
    a.init(n);
    for (ll i = 0; i < n; i++) {
        ll el;
        cin >> el;
        a.tree[i - 1 + a.size].v[el] = 1;
    }
    a.build(0, 0, a.size);
    for (auto el: a.tree) {
        cout << el.k << ' ';
    }
    cout << '\n';
    while (q--) {
        ll t, x, y;
        cin >> t >> x >> y;
        x--;
        if (t == 1) {
            cout << a.ask(x, y, 0, 0, a.size) << '\n';
        } else {
            a.add(x, y, 0, 0, a.size);
        }
    }
}
