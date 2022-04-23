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
    int n, k;
    cin >> n >> k;

    vector<string> s(n);
    rep(i, n) cin >> s[i];

    int ans = 0;
    rep(bit, 1L << n)
    {
        vector<int> cnts(26);
        vector<int> idxs;
        rep(i, n)
        {
            if (bit & (1L << i))
            {
                idxs.push_back(i);
            }
        }
        for (auto idx : idxs)
        {
            for (auto c : s[idx])
            {
                cnts[c - 'a']++;
            }
        }
        int ans_tmp = 0;
        rep(i, 26)
        {
            if (cnts[i] == k)
                ans_tmp++;
        }
        chmax(ans, ans_tmp);
    }

    cout << ans << endl;

    return 0;
}