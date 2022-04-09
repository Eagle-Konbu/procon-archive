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

using mint = modint1000000007;

mint dp[100005][8];

struct Edge
{
    ll to;
    ll weight;
    Edge(ll to, ll weight) : to(to), weight(weight) {}
};
typedef vector<vector<ll>> Graph;
typedef vector<vector<Edge>> WeightedGraph;

const int inf = 500005;

int main()
{
    int n;
    string s;
    cin >> n >> s;

    dp[0][0] = 1;
    rep(i, n) rep(j, 8)
    {
        dp[i + 1][j] += dp[i][j];
        if (s[i] == 'a' && j == 0)
            dp[i + 1][j + 1] += dp[i][j];
        if (s[i] == 't' && j == 1)
            dp[i + 1][j + 1] += dp[i][j];
        if (s[i] == 'c' && j == 2)
            dp[i + 1][j + 1] += dp[i][j];
        if (s[i] == 'o' && j == 3)
            dp[i + 1][j + 1] += dp[i][j];
        if (s[i] == 'd' && j == 4)
            dp[i + 1][j + 1] += dp[i][j];
        if (s[i] == 'e' && j == 5)
            dp[i + 1][j + 1] += dp[i][j];
        if (s[i] == 'r' && j == 6)
            dp[i + 1][j + 1] += dp[i][j];
    }

    cout << dp[n][7].val() << endl;

    return 0;
}