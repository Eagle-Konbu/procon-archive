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
    vector<pair<string, string>> st(n);
    rep(i, n) cin >> st[i].first >> st[i].second;

    rep(i, n)
    {
        bool s_ok = true;
        rep(j, n)
        {
            if (j != i)
            {
                if (st[i].first == st[j].first || st[i].first == st[j].second)
                {
                    s_ok = false;
                }
            }
        }
        bool t_ok = true;
        rep(j, n)
        {
            if (j != i)
            {
                if (st[i].second == st[j].first || st[i].second == st[j].second)
                {
                    t_ok = false;
                }
            }
        }
        if (!s_ok && !t_ok)
        {
            cout << "No" << endl;
            return 0;
        }
    }

    cout << "Yes" << endl;

    return 0;
}