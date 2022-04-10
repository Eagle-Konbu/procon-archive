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

int n, x, y;

ll count(vector<int> &b)
{
    ll res = 0;
    if (b.size() == 0)
        return 0;

    int right = 0, x_cnt = 0, y_cnt = 0;
    rep(left, b.size())
    {
        while (right < (int)b.size() && (x_cnt == 0 || y_cnt == 0))
        {
            if (b[right] == x)
                x_cnt++;
            if (b[right] == y)
                y_cnt++;

            right++;
        }
        if (x_cnt > 0 && y_cnt > 0)
            res += b.size() + 1 - right;
        if (b[left] == x)
            x_cnt--;
        if (b[left] == y)
            y_cnt--;
    }
    return res;
}

int main()
{
    cin >> n >> x >> y;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    ll ans = 0;

    rep(i, n)
    {
        vector<int> b;
        while (i < n && (y <= a[i] && a[i] <= x))
            b.push_back(a[i++]);
        ans += count(b);
    }

    cout << ans << endl;

    return 0;
}