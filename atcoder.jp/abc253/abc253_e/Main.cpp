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

using mint = modint998244353;

mint dp[1003][5003];

int main()
{
    ll n, m, k;
    cin >> n >> m >> k;

    if (m == 1)
    {
        cout << 1 << endl;
        return 0;
    }

    reps(i, m) dp[0][i] = 1;

    reps(i, n - 1)
    {
        fenwick_tree<mint> fw(m + 1);
        reps(j, m) fw.add(j, dp[i - 1][j]);
        reps(j, m)
        {
            if (k != 0)
            {
                if (j + k <= m)
                    dp[i][j] += fw.sum(j + k, m + 1);
                if (1 <= j - k)
                    dp[i][j] += fw.sum(1, (j - k) + 1);
            }
            else
            {
                dp[i][j] += fw.sum(1, m + 1);
            }
        }
    }

    mint ans = 0;

    reps(i, m) ans += dp[n - 1][i];

    cout << ans.val() << endl;

    return 0;
}