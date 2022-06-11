#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
typedef pair<ll, ll> P;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define reps(i, n) for (ll i = 1; i <= (ll)(n); i++)
#define rrep(i, n) for (ll i = (ll)n - 1; i >= 0; i--)
#define rreps(i, n) for (ll i = (ll)n; i > 0; i--)
#define SORT(x) sort(x.begin(), x.end())
#define ERASE(x) x.erase(unique(x.begin(), x.end()), x.end())
#define POSL(x, v) (lower_bound(x.begin(), x.end(), v) - x.begin())
#define POSU(x, v) (upper_bound(x.begin(), x.end(), v) - x.begin())
#define all(x) x.begin(), x.end()

template <typename T>
bool chmax(T &a, const T &b)
{
    if (a < b)
    {
        a = b;
        return true;
    }
    return false;
}
template <typename T>
bool chmin(T &a, const T &b)
{
    if (a > b)
    {
        a = b;
        return true;
    }
    return false;
}

struct Edge
{
    ll to;
    ll weight;
    Edge(ll to, ll weight) : to(to), weight(weight) {}
};
typedef vector<vector<ll>> Graph;
typedef vector<vector<Edge>> WeightedGraph;

int main()
{
    ll x, a, d, n;
    cin >> x >> a >> d >> n;

    ll max_item = max(a + (n - 1) * d, a);
    ll min_item = min(a + (n - 1) * d, a);

    if (max_item <= x)
    {
        cout << x - max_item << endl;
        return 0;
    }
    if (min_item >= x)
    {
        cout << min_item - x << endl;
        return 0;
    }

    ll n_min = 1 + (x - a) / d, n_max = 2 + (x - a) / d;

    ll ans = LONG_LONG_MAX;
    for (ll i = n_min; i <= n_max; i++)
    {
        ll sign = (x - (a + (i - 1) * d)) < 0 ? -1 : 1;
        chmin(ans, sign * (x - (a + (i - 1) * d)));
    }

    cout << ans << endl;

    return 0;
}