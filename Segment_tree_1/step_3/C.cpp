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

vector<ll> out;

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
            ll mx = (lx + rx) >> 1;
            if (i < mx) {
                add(i, 2 * x + 1, lx, mx);
            } else {
                add(i, 2 * x + 2, mx, rx);
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
    ll n;
    cin >> n;
    vector<ll> was(n + 1, -1);
    vector<ll> ans(n + 1);
    n *= 2;
    segtree a;
    a.init(n);
    for (ll i = 0; i < n; i++) {
        ll el;
        cin >> el;
        if (was[el] == -1) {
            was[el] = i;
        } else {
            ans[el] = a.ask(was[el], i, 0, 0, a.size);
            a.add(was[el], 0, 0, a.size);

        }
    }
    n /= 2;
    for (ll i = 1; i <= n; i++) cout << ans[i] << ' ';
}