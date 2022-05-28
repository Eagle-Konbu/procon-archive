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

template <typename T>
bool chmax(T &a, const T &b)
{
    if (a < b)
    {
        a = b;
        return true;
    }
    return false;
}
template <typename T>
bool chmin(T &a, const T &b)
{
    if (a > b)
    {
        a = b;
        return true;
    }
    return false;
}

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
    ll q;
    cin >> q;

    map<ll, ll> cnts;
    set<ll> s;

    rep(i, q)
    {
        ll t;
        cin >> t;

        if (t == 1)
        {
            ll x;
            cin >> x;
            if (!cnts.count(x))
                cnts[x] = 0;
            cnts[x]++;
            s.insert(x);
        }
        else if (t == 2)
        {
            ll x, c;
            cin >> x >> c;
            if (cnts[x] <= c)
            {
                cnts[x] = 0;
                s.erase(x);
            }
            else
            {
                cnts[x] -= c;
            }
        }
        else
        {
            ll min = *s.begin();
            ll max = *s.rbegin();
            cout << max - min << endl;
        }
    }

    return 0;
}