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

int main()
{
    int n;
    cin >> n;

    Graph g(n);
    rep(i, n - 1)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> d(n, -1);
    d[0] = 0;

    queue<int> que;
    que.push(0);
    while (!que.empty())
    {
        int v = que.front();
        que.pop();

        for (auto vv : g[v])
        {
            if (d[vv] != -1)
                continue;
            d[vv] = d[v] + 1;
            que.push(vv);
        }
    }

    int cnt1 = 0;
    int cnt0 = 0;
    rep(i, n)
    {
        if (d[i] % 2 == 0)
            cnt0++;
        else
            cnt1++;
    }

    int mod = 0;
    if (cnt1 > cnt0)
        mod = 1;

    vector<int> ans;
    rep(i, n) if (d[i] % 2 == mod) ans.push_back(i + 1);

    rep(i,n/2) {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}