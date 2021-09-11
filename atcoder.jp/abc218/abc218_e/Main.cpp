#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

int main()
{
    int n, m;
    cin >> n >> m;

    ll ans = 0;
    vector<tuple<int, int, int>> edges(m);
    dsu d(n);
    rep(i, m)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if (c >= 0)
        {
            edges[i] = make_tuple(c, a - 1, b - 1);
            ans += c;
        }
        else
        {
            d.merge(a - 1, b - 1);
        }
    }
    sort(edges.begin(), edges.end());

    for (auto e : edges)
    {
        int c = get<0>(e), a = get<1>(e), b = get<2>(e);
        if (d.same(a, b))
            continue;

        d.merge(a, b);
        ans -= c;
    }

    cout << ans << endl;

    return 0;
}