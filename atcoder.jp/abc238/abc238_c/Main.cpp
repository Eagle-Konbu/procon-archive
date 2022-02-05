#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define reps(i, n) for (ll i = 1; i <= (ll)(n); i++)
#define rrep(i, n) for (ll i = (ll)n - 1; i >= 0; i--)
#define rreps(i, n) for (ll i = (ll)n; i > 0; i--)

typedef modint998244353 mint;

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
    ll n;
    cin >> n;

    mint ans = 0;

    if (n < 10)
    {
        reps(i, n) ans += i;
    }
    else
    {
        for (ll i = 1; i <= 18; i++)
        {
            if (n < powl(10, i))
            {
                ans += mint(n - (ll)powl(10, i - 1) + 2) * mint(n - (ll)powl(10, i - 1) + 1) * mint(2).inv();
                break;
            }
            else
            {
                ans += mint((ll)powl(10, i) - (ll)pow(10, i - 1) + 1) * mint((ll)powl(10, i) - (ll)pow(10, i - 1)) * mint(2).inv();
            }
        }
    }

    cout << ans.val() << endl;
}