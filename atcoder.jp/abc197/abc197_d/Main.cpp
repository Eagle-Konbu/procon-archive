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
    int n;
    cin >> n;
    pair<double, double> p0, pn2, p1;
    cin >> p0.first >> p0.second;
    cin >> pn2.first >> pn2.second;

    pair<double, double> middle;

    middle.first = (p0.first + pn2.first) / 2;
    middle.second = (p0.second + pn2.second) / 2;

    p1.first = p0.first;
    p1.second = p0.second;

    p1.first -= middle.first;
    p1.second -= middle.second;
    const double theta = 2 * M_PI / n;

    double x,y;
    x = p1.first * cos(theta) - p1.second * sin(theta);
    y = p1.first * sin(theta) + p1.second * cos(theta);

    x += middle.first;
    y += middle.second;

    cout << x << " " << y << endl;

    return 0;
}