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

ll nCk(int n, int k)
{
    ll x = 1;
    ll y = 1;
    ll z = 1;

    rep(i, n) x *= n - i;
    rep(i, n - k) y *= n - k - i;
    rep(i, k) z *= k - i;

    return (x / (y * z));
}

__int128_t fact(__int128_t n)
{
    if (n == 0 || n == 1)
        return 1;
    else
        return n * fact(n - 1);
}

__int128_t comb(__int128_t m, __int128_t n)
{
    return fact(m) / (fact(n) * fact(m - n));
}

int main()
{
    ll n;
    cin >> n;

    vector a(n, vector<ll>());

    rep(i, n)
    {
        rep(j, i + 1)
        {
            if (j == 0 || j == i)
                a[i].push_back(1);
            else
                a[i].push_back(a[i - 1][j - 1] + a[i - 1][j]);
        }
        for(auto x : a[i]) {
            cout << x << " ";
        }
        cout << endl;
    }

    return 0;
}