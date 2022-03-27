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

bool dp[200005][2];

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);

    rep(i, n) cin >> a[i];
    rep(i, n) cin >> b[i];

    dp[0][0] = true, dp[0][1] = true;

    rep(i, n)
    {
        if (i == 0)
            continue;
        if (dp[i - 1][0] && abs(a[i - 1] - a[i]) <= k)
            dp[i][0] = true;
        if (dp[i - 1][1] && abs(b[i - 1] - a[i]) <= k)
            dp[i][0] = true;
        if (dp[i - 1][0] && abs(a[i - 1] - b[i]) <= k)
            dp[i][1] = true;
        if (dp[i - 1][1] && abs(b[i - 1] - b[i]) <= k)
            dp[i][1] = true;
    }

    cout << ((dp[n - 1][0] || dp[n - 1][1]) ? "Yes" : "No") << endl;

    return 0;
}