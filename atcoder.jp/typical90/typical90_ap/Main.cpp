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

using mint = modint1000000007;

int main()
{
    int k;
    cin >> k;

    auto digit_sum = [&](int n)
    {
        int res = 0;
        while (n > 0)
        {
            res += n % 10;
            n /= 10;
        }
        return res;
    };

    if (digit_sum(k) % 9 != 0)
    {
        cout << 0 << endl;
        return 0;
    }

    vector<mint> dp(k + 1, 0);

    dp[0] = 1;

    reps(i, k) reps(j, min((int)i, 9))
    {
        dp[i] += dp[i - j];
    }

    cout << dp[k].val() << endl;

    return 0;
}