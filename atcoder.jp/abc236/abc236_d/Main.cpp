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

int n;
vector<vector<int>> a;
int ans = 0;
void dfs(vector<bool> used, int x)
{
    int idx = -1;
    rep(i, n * 2) if (!used[i])
    {
        idx = i;
        break;
    }
    if (idx == -1)
    {
        ans = max(ans, x);
        return;
    }

    used[idx] = true;
    rep(i, n * 2) if (!used[i] && idx != i)
    {
        used[i] = true;
        dfs(used, x ^ a[idx][i]);
        used[i] = false;
    }
}

int main()
{
    cin >> n;
    a = vector<vector<int>>(2 * n, vector<int>(2 * n));
    rep(i, 2 * n) for (int j = i + 1; j < 2 * n; j++)
    {
        cin >> a[i][j];
        a[j][i] = a[i][j];
    }

    vector<bool> used(n * 2);
    dfs(used, 0);

    cout << ans << endl;

    return 0;
}