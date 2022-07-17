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

int main()
{
    ll n, x, y;
    cin >> n >> x >> y;

    if (n == 1)
    {
        cout << 0 << endl;
        return 0;
    }

    queue<pair<P, P>> que;
    que.push({{n, 1}, {0, 0}});

    ll ans = 0;

    while (!que.empty())
    {
        auto state = que.front();
        que.pop();

        chmax(ans, state.second.second);
        // cout << state.second.second << endl;
        // if(state.second.first == 1) {
        //     chmax(ans, state.second.second);
        // }

        if (state.first.first - 1 >= 1)
        {
            que.push({{state.first.first - 1, state.first.second}, {state.first.first, state.second.second + state.first.second * x}});
        }
        if (state.second.first - 1 >= 1)
        {
            que.push({{state.second.first - 1, state.first.second + state.second.second}, {state.second.first - 1, state.second.second * y}});
        }
    }

    // ll ans = 0;
    // queue<pair<vector<ll>, vector<ll>>> que;
    // vector<ll> red_first(n + 1, 0);
    // red_first[n] = 1;
    // que.push({red_first, vector<ll>(n + 1, 0)});

    // while (!que.empty())
    // {
    //     auto state = que.front();
    //     que.pop();

    //     chmax(ans, state.second[1]);
    //     cout << state.second[1] << endl;

    //     reps(i, n)
    //     {
    //         if (i == 1)
    //             continue;

    //         vector<ll> new_red(n + 1, 0);
    //         vector<ll> new_blue(n + 1, 0);
    //         rep(j, n + 1)
    //         {
    //             new_red[j] = state.first[j];
    //             new_blue[j] = state.second[j];
    //         }
    //         // reps(j, state.first[i])
    //         // {
    //         //     new_red[i - 1] = j;
    //         //     new_red[i] -= j;
    //         //     new_blue[i] = j * x;
    //         //     que.push({new_red, new_blue});
    //         // }
    //         new_red[i - 1] += state.first[i];
    //         new_blue[i] = state.first[i] * x;
    //         new_red[i] = 0;
    //         que.push({new_red, new_blue});
    //     }

    //     reps(i, n)
    //     {
    //         if (i == 1)
    //             continue;
    //         vector<ll> new_red(n + 1, 0);
    //         vector<ll> new_blue(n + 1, 0);
    //         rep(j, n + 1)
    //         {
    //             new_red[j] = state.first[j];
    //             new_blue[j] = state.second[j];
    //         }
    //         // reps(j, state.second[i])
    //         // {
    //         //     new_red[i - 1] = j;
    //         //     new_blue[i] -= j;
    //         //     new_blue[i - 1] = j * y;
    //         //     que.push({new_red, new_blue});
    //         // }
    //         new_red[i - 1] += state.second[i];
    //         new_blue[i] = state.second[i] * y;
    //         new_blue[i] = 0;
    //         que.push({new_red, new_blue});
    //     }
    // }

    cout << ans << endl;

    return 0;
}