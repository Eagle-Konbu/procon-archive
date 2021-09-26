#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
typedef pair<ll, ll> P;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
typedef modint998244353 mint;

int main()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    mint dp[n + 1][10];
    memset(dp, 0, sizeof(dp));
    dp[1][a[1]] = 1;
    for (int i = 1; i <= n - 1; i++)
    {
        rep(j, 10)
        {
            dp[i + 1][(j + a[i + 1]) % 10] += dp[i][j];
            dp[i + 1][(j * a[i + 1]) % 10] += dp[i][j];
        }
    }

    rep(i, 10) cout << dp[n][i].val() << endl;

    return 0;
}