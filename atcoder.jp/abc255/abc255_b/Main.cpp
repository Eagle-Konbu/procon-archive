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
    ll n, k;
    cin >> n >> k;
    vector<ll> a(k);
    vector<P> xy(n);
    rep(i, k) cin >> a[i];

    rep(i, n)
    {
        ll x, y;
        cin >> x >> y;
        xy[i] = {x, y};
    }

    double ans = 0;
    rep(i, n)
    {
        double ans_tmp = DBL_MAX;
        rep(j, k)
        {
            double dis = sqrt((xy[i].first - xy[a[j] - 1].first) * (xy[i].first - xy[a[j] - 1].first) + (xy[i].second - xy[a[j] - 1].second) * (xy[i].second - xy[a[j] - 1].second));
            if(ans_tmp > dis) ans_tmp = dis;
        }
        if(ans < ans_tmp) ans = ans_tmp;
    }

    printf("%0.18lf\n", ans);

    return 0;
}