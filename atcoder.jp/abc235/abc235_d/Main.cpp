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
    ll a, n;
    cin >> a >> n;

    ll m = 1e6;

    vector<ll> d(m + 1, -1);
    d[1] = 0;
    queue<ll> q;

    q.push(1);

    while (!q.empty())
    {
        ll from = q.front();
        q.pop();

        ll to1 = from * a;
        if (to1 < m && d[to1] == -1)
        {
            d[to1] = d[from] + 1;
            q.push(to1);
        }

        if (from >= 10 && from % 10 != 0)
        {
            string str = to_string(from);
            ll to2 = stoi(str[str.length() - 1] + str.substr(0, str.length() - 1));
            if(to2 < m && d[to2] == -1) {
                d[to2] = d[from] + 1;
                q.push(to2);
            }
        }
    }

    cout << d[n] << endl;

    return 0;
}