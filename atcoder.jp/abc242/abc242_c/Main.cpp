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

#define INF 1000005
typedef modint998244353 mint;

mint dp[INF][10] = {0};

int main()
{
    int n;
    cin >> n;

    rep(i, 10) dp[1][i] = 1;

    for (int i = 2; i <= n; i++)
    {
        reps(j, 9)
        {
            if (j - 1 >= 1)
                dp[i][j] += dp[i - 1][j - 1];
            dp[i][j] += dp[i - 1][j];
            if (j + 1 <= 9)
                dp[i][j] += dp[i - 1][j + 1];
        }
    }

    mint ans = 0;
    reps(i, 9)
    {
        ans += dp[n][i];
    }

    cout << ans.val() << endl;

    return 0;
}