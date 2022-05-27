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
    ll n;
    cin >> n;
    vector<P> lr;
    rep(i, n)
    {
        ll l, r;
        cin >> l >> r;
        lr.push_back({l, r});
    }

    vector<ll> l(n), r(n);
    rep(i, n)
    {
        l[i] = lr[i].first;
        r[i] = lr[i].second;
    }

    vector<vector<double>> p(100, vector<double>(100));

    rep(i, n)
    {
        for (int j = i + 1; j < n; ++j)
        {
            ll cnt_all = 0, cnt = 0;
            for (int x = l[i]; x <= r[i]; x++)
            {
                for (int y = l[j]; y <= r[j]; y++)
                {
                    cnt_all++;
                    if (x > y)
                        cnt++;
                }
            }
            p[i][j] = (double)cnt / cnt_all;
        }
    }

    double ans = 0;

    rep(i, n) for (int j = i + 1; j < n; j++)
    {
        ans += p[i][j];
    }

    printf("%.20lf\n", ans);

    return 0;
}