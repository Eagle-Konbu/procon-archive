#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (int)(n); i++)

vector<vector<int>> G;
bool visited[2000];
void dfs(int v)
{
    if (visited[v])
        return;
    visited[v] = true;
    for (auto to : G[v])
        dfs(to);
}

int main()
{
    int n, m;
    cin >> n >> m;

    G.resize(n);
    rep(i, m)
    {
        int a, b;
        cin >> a >> b;
        G[a - 1].push_back(b - 1);
    }

    int ans = 0;
    rep(st, n)
    {
        rep(i, n) visited[i] = false;
        dfs(st);
        rep(i, n) if (visited[i]) ans++;
    }

    cout << ans << endl;
    
    return 0;
}