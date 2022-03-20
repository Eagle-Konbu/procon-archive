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
    string start, goal;
    vector<int> arr;
    rep(i, 3)
    {
        char s;
        cin >> s;
        start.push_back(s);
    }
    rep(i, 3)
    {
        char t;
        cin >> t;
        goal.push_back(t);
    }

    rep(i, 3)
    {
        if (start[i] == goal[0])
            arr.push_back(0);
        else if (start[i] == goal[1])
            arr.push_back(1);
        else
            arr.push_back(2);
    }

    ll cnt = 0;

    rep(i, 3)
    {
        rep(j, 3)
        {
            if (arr[i] > arr[j] && i < j)
            {
                cnt++;
            }
        }
    }

    if (cnt % 2 == 0)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }

    return 0;
}