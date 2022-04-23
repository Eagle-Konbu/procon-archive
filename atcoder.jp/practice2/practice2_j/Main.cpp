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

int op(int a, int b) { return max(a, b); };
int e() { return -1; }
int target;
bool f(int x) { return x < target; };

int main()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    segtree<int, op, e> seg(a);

    vector<int> res;
    while (q--)
    {
        int t;
        cin >> t;
        if (t == 2)
        {
            int l, r;
            cin >> l >> r;

            int ans = seg.prod(l - 1, r);
            res.push_back(ans);
        }
        else
        {
            int x, v;
            cin >> x >> v;
            if (t == 1)
            {
                seg.set(x - 1, v);
            }
            else
            {
                target = v;
                int ans = seg.max_right<f>(x - 1) + 1;
                res.push_back(ans);
            }
        }
    }

    for (auto x : res)
        cout << x << endl;

    return 0;
}