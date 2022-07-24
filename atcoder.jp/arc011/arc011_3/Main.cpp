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

bool adj(string s1, string s2)
{
    ll n = s1.size();
    ll idx = -1;
    rep(i, n) if (s1[i] != s2[i])
    {
        idx = i;
        break;
    }

    s1.erase(idx, 1);
    s2.erase(idx, 1);
    return s1 == s2;
}

int main()
{
    string first, last;
    cin >> first >> last;
    ll n;
    cin >> n;
    vector<string> words;
    words.push_back(first);
    rep(i, n)
    {
        string s;
        cin >> s;
        if (s != first && s != last)
            words.push_back(s);
    }
    words.push_back(last);

    if (first == last)
    {
        cout << 0 << endl
             << first << endl
             << last << endl;
        return 0;
    }

    Graph g(words.size());
    rep(i, words.size())
    {
        rep(j, words.size())
        {
            if (i == j || words[i] == words[j])
                continue;
            if (adj(words[i], words[j]))
            {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }

    vector<ll> dis(g.size(), -1);
    vector<ll> prev(g.size(), -1);
    queue<ll> que;
    que.push(0);
    while (!que.empty())
    {
        ll v = que.front();
        que.pop();
        for (auto vv : g[v])
        {
            if (dis[vv] == -1)
            {
                dis[vv] = dis[v] + 1;
                que.push(vv);
                prev[vv] = v;
            }
        }
    }
    if (dis[g.size() - 1] == -1)
    {
        cout << "-1" << endl;
        return 0;
    }

    vector<string> ans;
    cout << dis[g.size() - 1] << endl;
    for(ll i = g.size() - 1; i != 0; i = prev[i])
    {
        ans.push_back(words[i]);
    }
    reverse(all(ans));
    cout << first << endl;
    for (auto s : ans)
    {
        cout << s << endl;
    }

    return 0;
}