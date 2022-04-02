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
    vector<P> points(3);

    rep(i, 3)
    {
        int x, y;
        cin >> x >> y;
        points[i] = {x, y};
    }

    SORT(points);

    if (points[1].first == points[0].first)
    {
        if (points[2].second == points[0].second)
        {
            cout << points[2].first << " " << points[1].second << endl;
        }
        else
        {
            cout << points[2].first << " " << points[0].second << endl;
        }
    }
    else
    {
        if (points[0].second == points[1].second)
        {
            cout << points[0].first << " " << points[2].second << endl;
        }
        else{
            cout << points[0].first << " " << points[1].second << endl;
        }
    }

    return 0;
}