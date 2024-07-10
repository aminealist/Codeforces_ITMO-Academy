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
ll count = 0;

struct vertex {
    ll num = -1;
    ll v = 0;
};

vertex tree[2 * size - 1];

void alloc(ll l, ll r, ll v, ll x = 0, ll lx = 0, ll rx = size) {
    if (lx >= r || rx <= l) return;
    if (lx >= l && rx <= r) {
        tree[x].v = v;
        tree[x].num = count;
        return;
    }
    ll mx = (lx + rx) >> 1;
    alloc(l, r, v, 2 * x + 1, lx, mx);
    alloc(l, r, v, 2 * x + 2, mx, rx);
}

vertex ask(ll i, ll x = 0, ll lx = 0, ll rx = size) {
    if (rx - lx == 1) return tree[x];
    ll mx = (lx + rx) >> 1;
    vertex ans;
    if (i < mx) {
        ans = ask(i, 2 * x + 1, lx, mx);
    } else {
        ans = ask(i, 2 * x + 2, mx, rx);
    }
    return ans.num > tree[x].num ? ans : tree[x];
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
            count++;
            alloc(l, r, v);
        } else {
            ll i;
            cin >> i;
            cout << ask(i).v << '\n';
        }
    }
}