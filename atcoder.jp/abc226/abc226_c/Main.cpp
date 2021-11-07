#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define reps(i, n) for (ll i = 1; i <= (ll)(n); i++)
#define rrep(i, n) for (ll i = (ll)n - 1; i >= 0; i--)
#define rreps(i, n) for (ll i = (ll)n; i > 0; i--)
#define ALL(x) (x).begin, (x).end
#define pb push_back

vector<vector<int>> g;
ll ans = 0;
vector<bool> visited;
vector<bool> need;

void dfs(int v)
{
    visited[v] = true;
    for (auto vv : g[v])
    {
        if (visited[vv])
            continue;
        need[vv] = true;
        if (need[v])
            dfs(vv);
    }
}

int main()
{
    ll n;
    cin >> n;
    vector<ll> t(n), k(n);
    g.resize(n);
    need.resize(n);
    visited.resize(n);

    rep(i, n)
    {
        cin >> t[i] >> k[i];
        rep(j, k[i])
        {
            int a;
            cin >> a;
            a--;
            g[i].push_back(a);
        }
    }

    need[n - 1] = true;
    dfs(n - 1);

    rrep(i, n) if (need[i]) ans += t[i];

    cout << ans << endl;

    return 0;
}