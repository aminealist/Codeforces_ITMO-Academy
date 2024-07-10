#pragma GCC optimize("unroll-loops", "unswitch-loops")
#pragma GCC optimize("Ofast", "no-stack-protector")
#pragma GCC optimize("profile-reorder-functions", "tracer")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("vpt")
#pragma GCC optimize("fast-math")

#pragma GCC target("tune=native")

#include<bits/stdc++.h>


#define ll long long

using std::max;
using std::cout;
using std::cin;
using std::ios;
using std::ios_base;


const ll size = 131072;


struct vertex {
    ll v = 0;
};

vertex tree[2 * size - 1];

void alloc(ll l, ll r, ll v, ll x = 0, ll lx = 0, ll rx = size) {
    if (lx >= r || rx <= l) return;
    if (lx >= l && rx <= r) {
        tree[x].v = max(tree[x].v, v);
        return;
    }
    ll mx = (lx + rx) >> 1;
    alloc(l, r, v, 2 * x + 1, lx, mx);
    alloc(l, r, v, 2 * x + 2, mx, rx);
}

ll ask(ll i, ll x = 0, ll lx = 0, ll rx = size) {
    if (rx - lx == 1)[[unlikely]] return tree[x].v;
    ll mx = (lx + rx) >> 1;
    if (i < mx) {
        return max(ask(i, 2 * x + 1, lx, mx), tree[x].v);
    } else {
        return max(ask(i, 2 * x + 2, mx, rx), tree[x].v);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, m;
    cin >> n >> m;
    while (m--) {
        ll t;
        cin >> t;
        if (t == 1) {
            ll l, r, v;
            cin >> l >> r >> v;
            alloc(l, r, v);
        } else {
            ll i;
            cin >> i;
            cout << ask(i) << '\n';
        }
    }
}