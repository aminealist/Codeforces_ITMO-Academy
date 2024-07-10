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
    ll min = MOD;
    ll alloc = -1;

    ll get() const {
        return alloc == -1 ? min : alloc;
    }
};

vertex tree[2 * size - 1];


void push(ll x) {
    if (tree[x].alloc != -1) {
        tree[2 * x + 1].alloc = tree[2 * x + 2].alloc = tree[x].alloc;
        tree[x].alloc = -1;
    }
}

void relax(ll x) {
    tree[x].min = min(tree[2 * x + 1].get(), tree[2 * x + 2].get());
}


void build(ll x = 0, ll lx = 0, ll rx = size) {
    if (rx - lx != 1)[[unlikely]] {
        ll mx = (lx + rx) >> 1;
        build(2 * x + 1, lx, mx);
        build(2 * x + 2, mx, rx);
        relax(x);
    }
}

void allocate(ll l, ll r, ll v, ll x = 0, ll lx = 0, ll rx = size) {
    if (lx >= r || rx <= l) return;
    if (lx >= l && rx <= r) {
        tree[x].alloc = v;
        return;
    }
    ll mx = (lx + rx) >> 1;
    push(x);
    allocate(l, r, v, 2 * x + 1, lx, mx);
    allocate(l, r, v, 2 * x + 2, mx, rx);
    relax(x);
}

ll ask(ll l, ll r, ll x = 0, ll lx = 0, ll rx = size) {
    if (lx >= r || rx <= l) return MOD;
    if (lx >= l && rx <= r) return tree[x].get();
    ll mx = (lx + rx) >> 1;
    push(x), relax(x);
    return min(ask(l, r, 2 * x + 1, lx, mx), ask(l, r, 2 * x + 2, mx, rx));
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, m;
    cin >> n >> m;
    for (ll i = 0; i < n; i++) tree[size - 1 + i].min = 0;
    build();
    while (m--) {
        ll t;
        cin >> t;
        if (t == 1) {
            ll l, r, v;
            cin >> l >> r >> v;
            allocate(l, r, v);
        } else {
            ll l, r;
            cin >> l >> r;
            cout << ask(l, r) << '\n';
        }
    }
}