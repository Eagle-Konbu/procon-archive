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
    ll k;
    cin >> k;

    vector<ll> rem;
    for (ll i = 1; i * i <= k; i++)
    {
        if (k % i != 0)
            continue;
        rem.push_back(i);
        if (i != k / i)
            rem.push_back(k / i);
    }
    SORT(rem);

    ll ans = 0;
    rep(i, rem.size()) rep(j, rem.size())
    {
        if (j < i)
            continue;
        ll a = rem[i], b = rem[j];
        if (k / a < b)
            continue;
        if (k % (a * b) != 0)
            continue;
        ll c = k / (a * b);
        if (b <= c)
            ans++;
    }

    cout << ans << endl;

    return 0;
}
