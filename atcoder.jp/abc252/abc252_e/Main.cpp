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
    ll idx;
    Edge(ll to, ll weight, ll idx) : to(to), weight(weight), idx(idx) {}
};
typedef vector<vector<ll>> Graph;
typedef vector<vector<Edge>> WeightedGraph;

int main()
{
    int n, m;
    cin >> n >> m;
    WeightedGraph g(n);
    rep(i, m)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        g[a].push_back(Edge(b, c, i));
        g[b].push_back(Edge(a, c, i));
    }

    vector<int> ans(n);

    priority_queue<P, vector<P>, greater<P>> pq;
    vector<ll> d(n, LONG_LONG_MAX);
    d[0] = 0;
    pq.push({0, 0});
    while (!pq.empty())
    {
        auto [d_tmp, v] = pq.top();
        pq.pop();

        if (d[v] < d_tmp)
            continue;

        for (auto e : g[v])
        {
            if (d[e.to] > d[v] + e.weight)
            {
                d[e.to] = d[v] + e.weight;
                pq.push({d[e.to], e.to});
                ans[e.to] = e.idx;
            }
        }
    }

    reps(i, n - 1) cout << ans[i] + 1 << " ";
    cout << endl;
}