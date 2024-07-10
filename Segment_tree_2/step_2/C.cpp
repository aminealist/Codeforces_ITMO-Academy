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
    ll orbit = 0;
    ll andbit = 0;

    ll get() { return orbit | andbit; }
};

vertex tree[2 * size - 1];

void push(ll x) {
    tree[2 * x + 1].orbit = tree[2 * x + 1].orbit | tree[x].orbit;
    tree[2 * x + 2].orbit = tree[2 * x + 2].orbit | tree[x].orbit;
    tree[x].orbit = 0;
}

void relax(ll x) {
    tree[x].andbit = tree[2 * x + 1].get() & tree[2 * x + 2].get();
}


void composite(ll l, ll r, ll v, ll x = 0, ll lx = 0, ll rx = size) {
    if (lx >= r || rx <= l) return;
    if (lx >= l && rx <= r) {
        tree[x].orbit |= v;
        return;
    }
    ll mx = (lx + rx) >> 1;
    push(x);
    composite(l, r, v, 2 * x + 1, lx, mx);
    composite(l, r, v, 2 * x + 2, mx, rx);
    relax(x);
}

ll ask(ll l, ll r, ll x = 0, ll lx = 0, ll rx = size) {
    if (lx >= r || rx <= l) return -1;
    if (lx >= l && rx <= r) return tree[x].get();
    ll mx = (lx + rx) >> 1;
    push(x);
    relax(x);
    ll left = ask(l, r, 2 * x + 1, lx, mx);
    ll right = ask(l, r, 2 * x + 2, mx, rx);
    if (left == -1) return right;
    if (right == -1) return left;
    return left & right;
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
            composite(l, r, v);
        } else {
            ll l, r;
            cin >> l >> r;
            cout << ask(l, r) << '\n';
        }
    }
}