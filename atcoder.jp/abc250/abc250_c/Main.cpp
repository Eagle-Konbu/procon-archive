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
    int n, q;
    cin >> n >> q;
    // vector<int> x(q);
    // rep(i, q) cin >> x[i];

    vector<int> positions(n + 1);
    reps(i, n) positions[i] = i;
    vector<int> balls(n + 1);
    reps(i, n) balls[i] = i;

    while (q--)
    {
        int x;
        cin >> x;
        if (positions[x] == n)
        {
            int prev_ball_num = balls[positions[x] - 1];
            swap(balls[positions[x]], balls[positions[x] - 1]);
            swap(positions[x], positions[prev_ball_num]);
        }
        else
        {
            int next_ball_num = balls[positions[x] + 1];
            swap(balls[positions[x]], balls[positions[x] + 1]);
            swap(positions[x], positions[next_ball_num]);
        }
    }

    reps(i,n) cout << balls[i] << " ";
    cout << endl;

    return 0;
}