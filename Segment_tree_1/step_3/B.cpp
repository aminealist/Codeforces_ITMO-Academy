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


    void build(ll x, ll lx, ll rx) {
        if (rx - lx != 1) [[likely]] {
            ll mx = (lx + rx) >> 1;
            build(2 * x + 1, lx, mx);
            build(2 * x + 2, mx, rx);
            tree[x].sum = tree[2 * x + 1].sum + tree[2 * x + 2].sum;
        }
    }

    void init(ll n) {
        size = 1;
        while (size < n) size *= 2;
        tree.resize(2 * size - 1);
        for (ll i = 0; i < n; i++) tree[size + i - 1].sum = 1;
        build(0, 0, size);
    }

    void ans(ll k, ll x, ll lx, ll rx) {
        if (rx - lx == 1) [[unlikely]] {
            tree[x].sum = 0;
            out.push_back(rx);
        } else [[likely]] {
            ll mx = (rx + lx) >> 1;
            if (tree[2 * x + 1].sum >= k) [[likely]] {
                ans(k, 2 * x + 1, lx, mx);
            } else {
                ans(k - tree[2 * x + 1].sum, 2 * x + 2, mx, rx);
            }
            tree[x].sum = tree[2 * x + 1].sum + tree[2 * x + 2].sum;
        }
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n;
    cin >> n;
    segtree a;
    a.init(n);
    vector<ll> p(n);
    for (auto &el: p) cin >> el;
    for (ll i = n - 1; i >= 0; i--) {
        a.ans(a.tree[0].sum - p[i], 0, 0, a.size);
    }
    reverse(out.begin(), out.end());
    for (auto el: out) cout << el << ' ';
}