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
    ll sum = 0;
    ll plus = 0;

    ll get(ll lx, ll rx) const {
        return sum + (rx - lx) * plus;
    }
};

vertex tree[2 * size - 1];

void push(ll x) {
    tree[2 * x + 1].plus += tree[x].plus;
    tree[2 * x + 2].plus += tree[x].plus;
    tree[x].plus = 0;
}

void relax(ll x, ll lx, ll rx) {
    ll mx = (lx + rx) >> 1;
    tree[x].sum = tree[2 * x + 1].get(lx, mx) + tree[2 * x + 2].get(mx, rx);
}


void plus(ll l, ll r, ll v, ll x = 0, ll lx = 0, ll rx = size) {
    if (lx >= r || rx <= l) return;
    if (lx >= l && rx <= r) {
        tree[x].plus += v;
        return;
    }
    ll mx = (lx + rx) >> 1;
    push(x);
    plus(l, r, v, 2 * x + 1, lx, mx);
    plus(l, r, v, 2 * x + 2, mx, rx);
    relax(x, lx, rx);
}

ll ask(ll l, ll r, ll x = 0, ll lx = 0, ll rx = size) {
    if (lx >= r || rx <= l) return 0;
    if (lx >= l && rx <= r) return tree[x].get(lx, rx);
    ll mx = (lx + rx) >> 1;
    push(x);
    relax(x, lx, rx);
    return ask(l, r, 2 * x + 1, lx, mx) + ask(l, r, 2 * x + 2, mx, rx);
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
            plus(l, r, v);
        } else {
            ll l, r;
            cin >> l >> r;
            cout << ask(l, r) << '\n';
        }
    }
}