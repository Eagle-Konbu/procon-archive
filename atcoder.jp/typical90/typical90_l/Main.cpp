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
    int h, w, q;
    cin >> h >> w >> q;

    dsu uf(h * w);
    vector red(h, vector<bool>(w, false));

    vector<P> dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    rep(i, q)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int r, c;
            cin >> r >> c;
            r--;
            c--;
            red[r][c] = true;
            rep(i, 4)
            {
                if (c + dir[i].first >= 0 && r + dir[i].second >= 0 && c + dir[i].first < w && r + dir[i].second < h)
                {
                    if (red[r + dir[i].second][c + dir[i].first])
                    {
                        uf.merge(w * r + c, w * (r + dir[i].second) + (c + dir[i].first));
                    }
                }
            }
        }
        else
        {
            int ra, ca, rb, cb;
            cin >> ra >> ca >> rb >> cb;
            ra--;
            ca--;
            rb--;
            cb--;
            if (uf.same(w * ra + ca, w * rb + cb) && red[ra][ca] && red[rb][cb])
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "No" << endl;
            }
        }
    }

    return 0;
}