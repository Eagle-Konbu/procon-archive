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
    ll n, x;
    cin >> n >> x;
    string s;
    cin >> s;

    ll ans = x;

    ll d_cnt = 0;
    bool overflowing = false;

    rep(i, n)
    {
        if (s[i] == 'U')
        {
            if (overflowing)
            {
                d_cnt--;
                if (d_cnt == 0)
                {
                    overflowing = false;
                }
                continue;
            }
            ans /= 2;
        }
        else if (s[i] == 'L')
        {
            if (overflowing)
            {
                d_cnt++;
                continue;
            }
            if (ans > LONG_LONG_MAX / 2)
            {
                overflowing = true;
                d_cnt++;
                continue;
            }
            ans *= 2;
        }
        else
        {
            if (overflowing)
            {
                d_cnt++;
                continue;
            }
            if (ans > (LONG_LONG_MAX - 1) / 2)
            {
                overflowing = true;
                d_cnt++;
                continue;
            }
            ans *= 2;

            ans++;
        }
    }

    cout << ans << endl;

    return 0;
}