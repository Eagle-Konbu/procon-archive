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

int main()
{
    int n, m;
    cin >> n >> m;
    const int INF = 1e9;
    vector<vector<int>> d(n, vector<int>(n, INF));
    rep(i, n) d[i][i] = 0;
    rep(i, m)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;
        d[a][b] = c;
    }

    ll ans = 0;
    rep(k, n)
    {
        rep(i, n) rep(j, n)
        {
            d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            if(d[i][j] != INF) ans += d[i][j];
        }
    }

    cout << ans << endl;

    return 0;
}