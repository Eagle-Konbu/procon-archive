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

ll cnt[1003][1003] = {};

int main()
{
    int n;
    cin >> n;
    rep(i, n)
    {
        int lx, ly, rx, ry;
        cin >> lx >> ly >> rx >> ry;
        cnt[lx][ly]++;
        cnt[rx][ly]--;
        cnt[lx][ry]--;
        cnt[rx][ry]++;
    }

    reps(i, 1001) rep(j, 1001 + 1)
    {
        cnt[i][j] += cnt[i - 1][j];
    }
    rep(i, 1001 + 1) reps(j, 1001)
    {
        cnt[i][j] += cnt[i][j - 1];
    }

    vector<ll> ans(n + 1);

    rep(i, 1001) rep(j, 1001)
    {
        ans[cnt[i][j]]++;
    }

    reps(i, n) cout << ans[i] << endl;

    return 0;
}