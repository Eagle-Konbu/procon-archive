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

using mint = modint998244353;

mint dp[2003][2003][2];

int main()
{
    int n, m, k, s, t, x;
    cin >> n >> m >> k >> s >> t >> x;
    s--;
    t--;
    x--;

    Graph g(n);
    rep(i, m)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    rep(i, n + 1)
    {
        if (i == s)
            dp[0][i][0] = 1;
        else
            dp[0][i][0] = 0;
        dp[0][i][1] = 0;
    }

    reps(i, k)
    {
        rep(j, n)
        {
            for (auto k : g[j])
            {
                rep(l, 2)
                {
                    if (j != x)
                        dp[i][j][l] += dp[i - 1][k][l];
                    else
                        dp[i][j][l] += dp[i - 1][k][1 - l];
                }
            }
        }
    }

    cout << dp[k][t][0].val() << endl;

    return 0;
}