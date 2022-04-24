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
    int n;
    cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    int m = *max_element(all(a));

    vector<int> cnts(m + 1);
    rep(i, n) cnts[a[i]]++;

    auto divisors = [&](int x)
    {
        vector<int> res;
        for (int i = 1; i * i <= x; i++)
        {
            if (x % i == 0)
            {
                res.push_back(i);
                if (i * i != x)
                    res.push_back(x / i);
            }
        }
        return res;
    };

    ll ans = 0;
    rep(i, n)
    {
        auto divs = divisors(a[i]);
        for (auto div : divs)
        {
            ans += 1LL * cnts[div] * cnts[a[i] / div];
        }
    }

    cout << ans << endl;

    return 0;
}