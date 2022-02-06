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
    string s;
    ll k;
    cin >> s >> k;
    ll n = s.size();

    vector<ll> cnt(n + 1);
    rep(i, n)
    {
        if (s[i] == '.')
        {
            cnt[i + 1] = cnt[i] + 1;
        }
        else
        {
            cnt[i + 1] = cnt[i];
        }
    }

    ll ans = 0, r = 0;
    rep(l, n)
    {
        while (r < n && cnt[r + 1] - cnt[l] <= k)
            r++;

        ans = max(ans, r - l);
    }

    cout << ans << endl;
    return 0;
}