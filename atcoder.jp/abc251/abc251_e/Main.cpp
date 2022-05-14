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

ll dp[300005][2];

int main()
{
    int n;
    cin >> n;

    vector<int> a(n + 1);
    reps(i, n) cin >> a[i];

    ll ans = 1e18;
    rep(t, 2)
    {
        dp[1][t] = a[1] * t, dp[1][1 - t] = 1e18;
        reps(i, n)
        {
            if (i < 2)
                continue;
            dp[i][0] = dp[i - 1][1];
            dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + a[i];
        }

        if (t == 0)
            ans = min(ans, dp[n][1]);
        if (t == 1)
            ans = min(ans, min(dp[n][0], dp[n][1]));
    }

    cout << ans << endl;

    return 0;
}