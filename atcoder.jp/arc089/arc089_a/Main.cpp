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

using mint = modint998244353;

mint dp[2003][2003][2];

int main()
{
    int n;
    cin >> n;
    vector<int> t(n);
    vector<P> points(n);

    rep(i, n) cin >> t[i] >> points[i].first >> points[i].second;

    P pos = {0, 0};

    int current_t = 0;
    rep(i, n)
    {
        int dis = abs(pos.first - points[i].first) + abs(pos.second - points[i].second);
        int max_move_cnt = t[i] - current_t;
        if (abs(max_move_cnt - dis) % 2 == 1 || dis > max_move_cnt)
        {
            cout << "No" << endl;
            return 0;
        }
        pos.first = points[i].first, pos.second = points[i].second;
        current_t = t[i];
    }

    cout << "Yes" << endl;

    return 0;
}