/*
　 　　　　　　 ／)
(＼　　　 ﾊ　　/ ／)
(＼＼　 ノ_)　/彡／)
(＼ヽヽ(　　)｜彡／)
（ヾヾiﾉ￣￣`/彡ニノ
　ヽﾐﾐ(Д｀／彡三ツ
　 ヽ(￣￣￣￣ヽﾂ +
　　+ ＼＿＿＿ノ+ ＊
　+ 十 +　+ ＼ ￣ヽ
　　+ 十 ＊　+￣ヽ
　 + ＊　 +
*/
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

template <typename T>
ll inversion_number(vector<T> &a)
{
    ll n = a.size(), m = *max_element(all(a));
    fenwick_tree<T> fw(m);

    ll res = 0;

    rep(i, n)
    {
        res += fw.sum(a[i] - 1, m);
        fw.add(a[i] - 1, 1);
    }

    return res;
}

void dfs(Graph &g, vector<vector<ll>> &dp, vector<ll> &x, ll v, ll p = -1)
{
    vector<ll> tmp;
    tmp.push_back(x[v]);
    for (auto vv : g[v])
    {
        if (vv == p)
            continue;
        dfs(g, dp, x, vv, v);
    }

    for (auto vv : g[v])
    {
        if (vv == p)
            continue;
        for (auto vvv : dp[vv])
        {
            tmp.push_back(vvv);
        }
    }
    SORT(tmp);
    reverse(all(tmp));

    for (auto vv : tmp)
    {
        if (dp[v].size() >= 20)
            break;
        dp[v].push_back(vv);
    }
}

int main()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    rep(i, n) cin >> a[i];

    auto f = [&](ll m)
    {
        ll cnt = 0;
        for (auto x : a)
        {
            cnt += max(0LL, x - m);
        }
        return cnt;
    };

    ll ok = 2e9, ng = -1;

    while (abs(ok - ng) > 1)
    {
        ll mid = (ok + ng) / 2;
        if (f(mid) < k)
            ok = mid;
        else
            ng = mid;
    }

    auto asum = [&](ll l, ll r)
    {
        return (l + r) * (r - l + 1) / 2;
    };
    ll ans = 0;
    rep(i, n)
    {
        if (a[i] <= ok)
            continue;
        ans += asum(ok + 1, a[i]);
    }
    ans += ok * (k - f(ok));

    cout << ans << endl;

    return 0;
}