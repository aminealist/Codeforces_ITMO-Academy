#pragma GCC optimize("unroll-loops", "unswitch-loops")
#pragma GCC optimize("Ofast", "no-stack-protector")
#pragma GCC optimize("unroll-loops", "unswitch-loops")
#pragma GCC optimize("Ofast", "no-stack-protector")
#pragma GCC optimize("profile-reorder-functions", "tracer")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("vpt")
#pragma GCC optimize("fast-math")

#pragma GCC target("tune=native")

#include<bits/stdc++.h>


#define ll long long

using namespace std;

struct segtree {
    ll size;
    vector<ll> tree;

    void init(ll n) {
        size = 1;
        while (size < n) size *= 2;
        tree = vector<ll>(2 * size - 1, 0);
    }

    void repl(ll i, ll v, ll x, ll lx, ll rx) {
        if (rx - lx <= 1) {
            tree[x] = v;
        } else {
            ll mid = (lx + rx) / 2;
            if (i < mid) {
                repl(i, v, 2 * x + 1, lx, mid);
            } else {
                repl(i, v, 2 * x + 2, mid, rx);
            }
            tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
        }
    }

    void add(ll l, ll r, ll v, ll x, ll lx, ll rx) {
        if (l >= rx || r <= lx) {
            return;
        } else {
            if (lx >= l && rx <= r) {
                tree[x] += v;
                return;
            } else {
                ll mid = (lx + rx) / 2;
                add(l, r, v, 2 * x + 1, lx, mid);
                add(l, r, v, 2 * x + 2, mid, rx);
            }
        }
    }

    ll get(ll i, ll x, ll lx, ll rx) {
        if (rx - lx <= 1) {
            return tree[x];
        } else {
            ll mid = (lx + rx) / 2;
            if (i < mid) {
                return tree[x] + get(i, 2 * x + 1, lx, mid);
            }
            return tree[x] + get(i, 2 * x + 2, mid, rx);
        }
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, q, t, x, l, r;
    cin >> n >> q;
    segtree a;
    a.init(n);
//    for (auto el: a.tree) {
//        cout << el << ' ';
//    }
//    cout << "\n";
    for (ll i = 0; i < q; i++) {
        cin >> t;
        if (t == 1) {
            cin >> l >> r >> x;
            a.add(l, r, x, 0, 0, a.size);
        } else {
            cin >> x;
            cout << a.get(x, 0, 0, a.size) << "\n";
        }
    }
}