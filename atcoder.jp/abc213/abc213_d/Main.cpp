#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
typedef pair<ll, ll> P;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

vector<vector<int>> g;

void dfs(int v, int p)
{
    cout << v + 1 << endl;
    for (auto next : g[v])
    {
        if (next != p)
        {
            dfs(next, v);
            cout << v + 1 << endl;
        }
    }
}

int main()
{
    int n;
    cin >> n;
    g.resize(n);
    rep(i, n - 1)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    rep(i, n) sort(g[i].begin(), g[i].end());

    dfs(0, 0);
    return 0;
}