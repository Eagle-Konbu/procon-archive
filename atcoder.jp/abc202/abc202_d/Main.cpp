#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define reps(i, n) for (ll i = 1; i <= (ll)(n); i++)
#define rrep(i, n) for (ll i = (ll)n - 1; i >= 0; i--)
#define rreps(i, n) for (ll i = (ll)n; i > 0; i--)

ll c[61][61];

int main()
{
    ll a, b, k;
    cin >> a >> b >> k;

    c[0][0] = 1;
    rep(i, 60) rep(j, i + 1) c[i + 1][j] += c[i][j], c[i + 1][j + 1] += c[i][j];

    string ans;
    while (a + b > 0)
    {
        ll x = 0;
        if (a >= 1)
            x = c[a + b - 1][a - 1];
        
        if (k <= x)
            ans += 'a', a--;
        else
            ans += 'b', b--, k -= x;
    }

    cout << ans << endl;

    return 0;
}
