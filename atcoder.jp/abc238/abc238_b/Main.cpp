#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define reps(i, n) for (ll i = 1; i <= (ll)(n); i++)
#define rrep(i, n) for (ll i = (ll)n - 1; i >= 0; i--)
#define rreps(i, n) for (ll i = (ll)n; i > 0; i--)

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
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    vector<int> angles(n + 1);
    reps(i, n)
    {
        angles[i] = (angles[i - 1] + a[i - 1]) % 360;
    }

    sort(angles.begin(), angles.end());

    int ans = 0;
    reps(i, n)
    {
        if (angles[i] - angles[i - 1] > ans)
        {
            ans = angles[i] - angles[i - 1];
        }
    }
    if (angles[0] + 360 - angles[n] > ans)
    {
        ans = angles[0] + 360 - angles[n];
    }

    cout << ans << endl;
}