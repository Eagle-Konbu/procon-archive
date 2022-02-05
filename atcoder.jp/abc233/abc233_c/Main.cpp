#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define reps(i, n) for (ll i = 1; i <= (ll)(n); i++)
#define rrep(i, n) for (ll i = (ll)n - 1; i >= 0; i--)
#define rreps(i, n) for (ll i = (ll)n; i > 0; i--)

struct Edge
{
    ll to;
    ll weight;
    Edge(ll to, ll weight) : to(to), weight(weight) {}
};
typedef vector<vector<ll>> Graph;
typedef vector<vector<Edge>> WeightedGraph;

void dfs(ll pos, ll prod, ll n, ll x, vector<vector<ll>> &a, ll &ans)
{
    if (pos == n)
    {
        if (prod == x)
            ans++;
        return;
    }
    for (ll c : a[pos])
    {
        if (prod > x / c)
            continue;
        dfs(pos + 1, prod * c, n, x, a, ans);
    }
}

int main()
{
    ll n, x;
    cin >> n >> x;
    vector<ll> l(n);
    vector<vector<ll>> a(n);

    rep(i, n)
    {
        cin >> l[i];
        rep(j, l[i])
        {
            ll item;
            cin >> item;
            a[i].push_back(item);
        }
    }

    ll ans = 0;
    dfs(0, 1, n, x, a, ans);
    cout << ans << endl;
    return 0;
}