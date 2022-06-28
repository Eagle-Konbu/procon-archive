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

ll factorial(ll n)
{
    if (n == 1 || n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}

ll combination(ll a, ll b)
{
    return factorial(a) / (factorial(a - b) * factorial(b));
}

ll gcd(ll a, ll b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

ll lcm(ll a, ll b)
{
    return a / gcd(a, b) * b;
}

vector<ll> divisors(ll n, bool sorted = false)
{
    vector<ll> res;
    for (ll i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            res.push_back(i);
            if (i * i != n)
                res.push_back(n / i);
        }
    }
    if (sorted)
    {
        SORT(res);
    }

    return res;
}

vector<bool> eratosthenes(ll n)
{
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (ll p = 2; p <= n; p++)
    {
        if (!is_prime[p])
            continue;
        for (int q = p * 2; q <= n; q += p)
        {
            is_prime[q] = false;
        }
    }

    return is_prime;
}

template <typename T>
vector<T> compress(vector<T> a)
{
    vector<T> b = a;
    SORT(b);
    ERASE(b);

    vector<T> res(a.size());
    rep(i, a.size())
    {
        res[i] = POSL(b, a[i]);
    }

    return res;
}

struct Edge
{
    ll to;
    ll weight;
    Edge(ll to, ll weight) : to(to), weight(weight) {}
};
typedef vector<vector<ll>> Graph;
typedef vector<vector<Edge>> WeightedGraph;

vector<ll> dijkstra(const WeightedGraph &g, ll s)
{
    vector<ll> dis(g.size(), LONG_LONG_MAX);
    dis[s] = 0;
    priority_queue<P, vector<P>, greater<P>> pq;

    pq.push({0, s});
    while (!pq.empty())
    {
        auto [current_dis, v] = pq.top();
        pq.pop();
        if (dis[v] < current_dis)
            continue;
        for (auto e : g[v])
        {
            if (chmin(dis[e.to], current_dis + e.weight))
            {
                pq.push({dis[e.to], e.to});
            }
        }
    }
    return dis;
}

vector<ll> topo_sort(const Graph &g)
{
    vector<ll> res;
    ll n = g.size();
    vector<ll> in_deg(n);

    rep(i, n) for (auto vv : g[i]) in_deg[vv]++;

    queue<ll> que;
    rep(i, n) if (in_deg[i] == 0) que.push(i);

    while (!que.empty())
    {
        ll v = que.front();
        res.push_back(v);
        que.pop();
        for (auto vv : g[v])
        {
            in_deg[vv]--;
            if (in_deg[vv] == 0)
                que.push(vv);
        }
    }

    return res;
}

ll f(ll x, vector<ll> &dp, Graph &g)
{
    if (dp[x] != 0)
        return dp[x];
    for (auto y : g[x])
    {
        chmax(dp[x], f(y, dp, g) + 1);
    }
    return dp[x];
}

int main()
{
    string s, t;
    cin >> s >> t;

    vector dp(s.length() + 1, vector<ll>(t.length() + 1));

    reps(i, s.length()) reps(j, t.length())
    {
        if (s[i - 1] == t[j - 1])
        {
            dp[i][j] = dp[i - 1][j - 1] + 1;
        }
        else
        {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    string ans = "";
    int i = s.length(), j = t.length();
    while (i > 0 && j > 0)
    {
        if (dp[i][j] == dp[i][j - 1])
            j--;
        else if (dp[i][j] == dp[i - 1][j])
            i--;
        else
        {
            ans = s[i - 1] + ans;
            i--;
            j--;
        }
    }
    cout << ans << endl;

    return 0;
}
