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

ll dp[101][100001];

int main()
{
    ll n, W;
    cin >> n >> W;
    vector<ll> w(n + 1), v(n + 1);
    reps(i, n) cin >> w[i] >> v[i];

    rep(i, n + 1) rep(j, 100001) dp[i][j] = 1e9+1;

    dp[0][0] = 0;
    reps(i, n) rep(j, 100001)
    {
        if (j - v[i] >= 0)
        {
            dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - v[i]] + w[i]);
        }
        else
        {
            dp[i][j] = dp[i - 1][j];
        }
    }

    int ans = 100000;
    while (dp[n][ans] > W)
        ans--;

    cout << ans << endl;

    return 0;
}