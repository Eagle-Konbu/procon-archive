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

using mint = modint1000000007;

bool all_same(vector<int> &a)
{
    int num = a[0];
    for (auto e : a)
    {
        if (e != num)
            return false;
    }
    return true;
}

int main()
{
    int h, w;
    cin >> h >> w;
    vector p(h, vector<int>(w));
    rep(i, h) rep(j, w) cin >> p[i][j];

    int ans = 0;

    rep(bit, 1L << h)
    {
        if (bit == 0)
            continue;
        vector<int> rows, cols;
        rep(i, h)
        {
            if (bit & (1L << i))
            {
                rows.push_back(i);
            }
        }
        rep(col, w)
        {
            vector<int> row_nums;
            for (auto row : rows)
            {
                row_nums.push_back(p[row][col]);
            }
            if (all_same(row_nums))
                cols.push_back(col);
        }
        map<int, int> cnts;
        int cnt = 0;
        for (auto col : cols)
        {
            cnts[p[rows[0]][col]]++;
            chmax(cnt, cnts[p[rows[0]][col]]);
        }
        chmax(ans, (int)rows.size() * cnt);
    }

    cout << ans << endl;

    return 0;
}