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
    ll n, m;
    cin >> n >> m;
    Graph g(n);

    rep(i, m)
    {
        ll a, b;
        cin >> a >> b;
        a--;
        b--;

        g[a].push_back(b);
        g[b].push_back(a);
    }
    ll q;
    cin >> q;

    while (q--)
    {
        ll x, k;
        cin >> x >> k;
        x--;

        set<ll> vertexs = {x};
        queue<P> que;
        que.push({x, 0});
        while (!que.empty())
        {
            auto [v, d] = que.front();
            que.pop();
            for (auto vv : g[v])
            {
                if (d + 1 <= k)
                    vertexs.insert(vv);
                if (d + 1 < k)
                    que.push({vv, d + 1});
            }
        }

        ll ans = 0;
        for (auto v : vertexs)
        {
            ans += v + 1;
        }
        cout << ans << endl;
    }

    return 0;
}