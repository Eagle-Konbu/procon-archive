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

int h, w;
int ans;
bool visited[20][20];
char grid[20][20];

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int dfs(int sx, int sy, int x, int y)
{
    if (sx == x && sy == y && visited[x][y])
        return 0;
    visited[x][y] = true;

    int res = INT_MIN;
    rep(i, 4)
    {
        int next_x = x + dx[i], next_y = y + dy[i];
        if (next_x < 0 || next_y < 0 || next_x >= h || next_y >= w || grid[next_x][next_y] == '#')
            continue;
        if ((sx != next_x || sy != next_y) && visited[next_x][next_y])
            continue;
        int v = dfs(sx, sy, next_x, next_y);
        res = max(res, v + 1);
    }
    visited[x][y] = false;
    return res;
}

int main()
{
    cin >> h >> w;

    rep(i, h) rep(j, w) cin >> grid[i][j];

    ans = -1;
    rep(i, h) rep(j, w)
    {
        ans = max(ans, dfs(i, j, i, j));
    }

    if (ans <= 2)
        ans = -1;
    cout << ans << endl;

    return 0;
}