#pragma GCC optimize("unroll-loops", "unswitch-loops")
#pragma GCC optimize("Ofast", "no-stack-protector")
#pragma GCC optimize("profile-reorder-functions", "tracer")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("vpt")
#pragma GCC optimize("fast-math")

#pragma GCC target("tune=native")

#include<bits/stdc++.h>


#define ll long long

using std::min;
using std::cout;
using std::cin;
using std::ios;
using std::ios_base;

const ll size = 131072;
const ll MOD = 1e9 + 7;


struct vertex {
    ll comp = 0;
    ll sum = 0;

    ll get() { return (comp * sum) % MOD; }
};

vertex tree[2 * size - 1];

void push(ll x) {
    tree[2 * x + 1].comp = (tree[2 * x + 1].comp * tree[x].comp) % MOD;
    tree[2 * x + 2].comp = (tree[2 * x + 2].comp * tree[x].comp) % MOD;
    tree[x].comp = 1;
}

void relax(ll x) {
    tree[x].sum = (tree[2 * x + 1].get() + tree[2 * x + 2].get()) % MOD;
}

void build(ll x = 0, ll lx = 0, ll rx = size) {
    if (rx - lx != 1)[[likely]] {
        ll mx = (lx + rx) >> 1;
        build(2 * x + 1, lx, mx);
        build(2 * x + 2, mx, rx);
        relax(x);
    }
}

void composite(ll l, ll r, ll c, ll x = 0, ll lx = 0, ll rx = size) {
    if (lx >= r || rx <= l) return;
    if (lx >= l && rx <= r) {
        tree[x].comp *= c;
        tree[x].comp %= MOD;
        return;
    }
    ll mx = (lx + rx) >> 1;
    push(x);
    composite(l, r, c, 2 * x + 1, lx, mx);
    composite(l, r, c, 2 * x + 2, mx, rx);
    relax(x);
}

ll ask(ll l, ll r, ll x = 0, ll lx = 0, ll rx = size) {
    if (lx >= r || rx <= l) return 0;
    if (lx >= l && rx <= r) return tree[x].get();
    ll mx = (lx + rx) >> 1;
    push(x);
    relax(x);
    return (ask(l, r, 2 * x + 1, lx, mx) + ask(l, r, 2 * x + 2, mx, rx)) % MOD;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, m;
    cin >> n >> m;
    for (ll i = 0; i < size - 1 + n; i++) tree[i].sum = tree[i].comp = 1;
    build();
    while (m--) {
        ll t;
        cin >> t;
        if (t == 1) {
            ll l, r, v;
            cin >> l >> r >> v;
            composite(l, r, v);
        } else {
            ll l, r;
            cin >> l >> r;
            cout << ask(l, r) << '\n';
        }
    }
}