#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define reps(i, n) for (ll i = 1; i <= (ll)(n); i++)
#define rrep(i, n) for (ll i = (ll)n - 1; i >= 0; i--)
#define rreps(i, n) for (ll i = (ll)n; i > 0; i--)

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
    string s;
    cin >> s;
    int n = s.length();

    int x = 0, y = 0;
    rep(i, n)
    {
        if (s[i] != 'a')
            break;
        x++;
    }
    rrep(i, n)
    {
        if (s[i] != 'a')
            break;
        y++;
    }

    if (x == n) {
        cout << "Yes" << endl;
        return 0;
    }

    if (x > y)
    {
        cout << "No" << endl;
        return 0;
    }

    for (int i = x; i < n - y; i++)
    {
        if (s[i] != s[x + n - y - i - 1])
        {
            cout << "No" << endl;
            return 0;
        }
    }

    cout << "Yes" << endl;
    return 0;
}