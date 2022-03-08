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

struct Edge
{
    ll to;
    ll weight;
    Edge(ll to, ll weight) : to(to), weight(weight) {}
};
typedef vector<vector<ll>> Graph;
typedef vector<vector<Edge>> WeightedGraph;

double dp[3003][3003] = {0};

int main()
{
    int n;
    cin >> n;
    vector<double> p(n + 1);
    reps(i, n) cin >> p[i];

    dp[0][0] = 1;

    reps(i, n) rep(j, i + 1)
    {
        if (j > 0)
            dp[i][j] = dp[i - 1][j] * (1 - p[i]) + dp[i - 1][j - 1] * p[i];
        else
            dp[i][j] = dp[i - 1][j] * (1 - p[i]);
    }

    double ans = 0;
    for (int i = n / 2 + 1; i <= n; i++)
        ans += dp[n][i];

    printf("%0.10lf\n", ans);

    return 0;
}