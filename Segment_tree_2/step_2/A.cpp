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
const ll INF = 1e15;

struct vertex {
    ll min = 0;
    ll plus = 0;

    ll val() const { return min + plus; }
};

vertex tree[2 * size - 1];

void push(ll x) {
    tree[2 * x + 1].plus += tree[x].plus;
    tree[2 * x + 2].plus += tree[x].plus;
    tree[x].plus = 0;
}

void relax(ll x) {
    tree[x].min = min(tree[2 * x + 1].val(), tree[2 * x + 2].val());
}

void plus(ll l, ll r, ll p, ll x = 0, ll lx = 0, ll rx = size) {
    if (lx >= r || rx <= l) return;
    if (lx >= l && rx <= r) {
        tree[x].plus += p;
        return;
    }
    ll mx = (lx + rx) >> 1;
    push(x);
    plus(l, r, p, 2 * x + 1, lx, mx);
    plus(l, r, p, 2 * x + 2, mx, rx);
    relax(x);
}

ll ask(ll l, ll r, ll x = 0, ll lx = 0, ll rx = size) {
    if (lx >= r || rx <= l) return INF;
    if (lx >= l && rx <= r) return tree[x].val();
    ll mx = (lx + rx) >> 1;
    push(x);
    relax(x);
    return min(ask(l, r, 2 * x + 1, lx, mx), ask(l, r, 2 * x + 2, mx, rx));
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
            ll ans = ask(l, r);
            cout << ans << '\n';
        }
    }
}