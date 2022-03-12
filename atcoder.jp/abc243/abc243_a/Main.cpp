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
    int v, a, b, c;
    cin >> v >> a >> b >> c;

    int n = 0;
    int s = v;
    while (true)
    {
        switch (n % 3)
        {
        case 0:
            if(s < a) {
                cout << "F" << endl;
                return 0;
            }
            s -= a;
            break;
        case 1:
            if (s < b)
            {
                cout << "M" << endl;
                return 0;
            }
            s -= b;
            break;
        case 2:
            if (s < c)
            {
                cout << "T" << endl;
                return 0;
            }
            s -= c;
            break;
        default:
            break;
        }
        n++;
    }

    return 0;
}