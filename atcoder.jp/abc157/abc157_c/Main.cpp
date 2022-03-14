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
    vector<int> s(m), c(m);
    rep(i, m) cin >> s[i] >> c[i];

    string num_str = "";
    rep(i, n) num_str += ".";

    rep(i, m)
    {
        if (num_str[s[i] - 1] != '.' && num_str[s[i] - 1] != c[i] + '0')
        {
            cout << -1 << endl;
            return 0;
        }

        num_str[s[i] - 1] = '0' + c[i];
    }
    if (num_str[0] == '0' && n > 1)
    {
        cout << -1 << endl;
        return 0;
    }

    rep(i, n)
    {
        if (num_str[i] != '.')
            continue;
        if (i == 0 && n > 1)
        {
            num_str[i] = '1';
        }
        else
        {
            num_str[i] = '0';
        }
    }

    cout << num_str << endl;

    return 0;
}