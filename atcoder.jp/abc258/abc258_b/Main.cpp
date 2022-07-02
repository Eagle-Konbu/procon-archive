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
    ll n;
    cin >> n;
    vector<string> str(n);
    rep(i, n) cin >> str[i];

    vector a(n, vector<ll>(n));
    rep(i, n) rep(j, n) a[i][j] = str[i][j] - '0';

    ll max_num = 0;
    rep(i, n) rep(j, n)
    {
        if (a[i][j] > max_num)
            max_num = a[i][j];
    }

    vector<P> max_pos;
    rep(i, n)
    {
        rep(j, n)
        {
            if (a[i][j] == max_num)
            {
                P pos = {i, j};
                max_pos.push_back(pos);
            }
        }
    }

    // for (auto pos : max_pos)
    // {
    //     cout << pos.first << " " << pos.second << endl;
    // }

    vector<string> ans_list;

    vector<P> dir_list = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0},
        {-1, -1},
        {-1, 1},
        {1, -1},
        {1, 1},
    };

    for (auto from : max_pos)
    {
        rep(dir_idx, 8)
        {
            string ans_tmp = to_string(a[from.first][from.second]);
            reps(i, n - 1)
            {
                ll row = (from.first + i * dir_list[dir_idx].first) % n;
                ll col = (from.second + i * dir_list[dir_idx].second) % n;
                while(row < 0) {
                    row += n;
                }
                while(col < 0) {
                    col += n;
                }
                ans_tmp += to_string(a[row][col]);
            }
            ans_list.push_back(ans_tmp);
        }
    }

    vector<ll> ans_num_list;
    for (auto str : ans_list)
    {
        ans_num_list.push_back(stoll(str));
    }

    cout << *max_element(all(ans_num_list)) << endl;

    return 0;
}