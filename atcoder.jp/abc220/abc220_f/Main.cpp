#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
typedef pair<ll, ll> P;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

vector<vector<int>> g;
vector<ll> sub;

void dfs(int i, int p, int d, ll &ans)
{
    ans += d;
    for (auto next : g[i])
    {
        if (next != p)
        {
            dfs(next, i, d + 1, ans);
            sub[i] += sub[next];
        }
    }
}

void dfs2(int i, int p, vector<ll> &ans, int n)
{
    for (auto next : g[i])
    {
        if (next != p)
        {
            ans[next] = ans[i] + n - 2 * sub[next];
            dfs2(next, i, ans, n);
        }
    }
}

int main()
{
    int n;
    cin >> n;
    g.resize(n);
    sub.resize(n);
    fill(sub.begin(), sub.end(), 1);

    rep(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<ll> ans(n, 0);
    dfs(0, 0, 0, ans[0]);
    dfs2(0, 0, ans, n);

    for (auto x : ans)
        cout << x << endl;

    return 0;
}