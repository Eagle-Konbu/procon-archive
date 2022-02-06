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
    vector<string> s(n), t(m);
    rep(i, n) cin >> s[i];
    rep(i, m) cin >> t[i];

    vector<bool> stops(n, false);

    int j = 0;
    rep(i, n)
    {
        if (s[i] == t[j])
        {
            stops[i] = true;
            j++;
        }
    }

    rep(i,n) {
        if(stops[i]) cout << "Yes" << endl;
        else cout << "No" << endl;
    }

    return 0;
}