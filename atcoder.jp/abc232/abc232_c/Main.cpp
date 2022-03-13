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

bool x[8][8], y[8][8];

int main()
{
    int n, m;
    cin >> n >> m;
    rep(i, m)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        x[a][b] = true;
        x[b][a] = true;
    }
    rep(i, m)
    {
        int c, d;
        cin >> c >> d;
        c--;
        d--;
        y[c][d] = true;
        y[d][c] = true;
    }

    vector<int> p(n);
    rep(i, n) p[i] = i;
    do
    {
        bool ok = true;
        rep(i, n) rep(j, n)
        {
            if (x[i][j] != y[p[i]][p[j]])
                ok = false;
        }
        if (ok)
        {
            cout << "Yes" << endl;
            return 0;
        }
    } while (next_permutation(all(p)));

    cout << "No" << endl;

    return 0;
}