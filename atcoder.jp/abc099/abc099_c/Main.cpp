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

int main()
{
    int n;
    cin >> n;

    Graph g(n + 1);

    rep(i, n)
    {
        g[i].push_back(i + 1);
        for (int j = 6; i + j <= n; j *= 6)
        {
            g[i].push_back(i + j);
        }
        for (int j = 9; i + j <= n; j *= 9)
        {
            g[i].push_back(i + j);
        }
    }

    vector<int> dist(n + 1, -1);
    dist[0] = 0;

    queue<int> que;
    que.push(0);

    while (!que.empty())
    {
        int v = que.front();
        que.pop();
        for (auto vv : g[v])
        {
            if (dist[vv] == -1)
            {
                que.push(vv);
                dist[vv] = dist[v] + 1;
            }
        }
    }

    cout << dist[n] << endl;

    return 0;
}