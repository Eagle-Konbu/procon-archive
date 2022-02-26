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
    int q;
    cin >> q;
    multiset<ll> a;

    rep(i, q)
    {
        int op;
        ll x, k;
        cin >> op >> x;
        if (op == 1)
        {
            a.insert(x);
            continue;
        }
        cin >> k;
        if (op == 2)
        {
            auto it = a.upper_bound(x);
            bool ok = true;
            rep(j, k)
            {
                if (it == a.begin())
                {
                    ok = false;
                    break;
                }
                it = prev(it);
            }
            cout << (ok ? *it : -1) << endl;
        }
        else
        {
            auto it = a.lower_bound(x);
            bool ok = true;
            rep(j, k - 1)
            {
                if (it == a.end())
                {
                    ok = false;
                    break;
                }
                it = next(it);
            }
            if (it == a.end())
                ok = false;
            cout << (ok ? *it : -1) << endl;
        }
    }

    return 0;
}