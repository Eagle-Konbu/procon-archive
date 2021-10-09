#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
typedef pair<ll, ll> P;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define reps(i, n) for (ll i = 1;; i <= (ll)(n); i++)
#define rrep(i, n) for (ll i = ((ll)(n)-1); i >= 0; i--)
#define rreps(i, n) for (ll i = ((ll)(n)); i > 0; i--)
#define ALL(x) (x).begin(), (x).end()
#define pb push_back

#define NMAX 50
#define MMAX 100

int main()
{
    int n, m;
    cin >> n >> m;
    char a[NMAX * 2][MMAX];

    rep(i, 2 * n)
    {
        rep(j, m) cin >> a[i][j];
    }

    vector<P> player(2 * n);
    rep(i, 2 * n)
    {
        player[i] = {0, -i};
    }

    rep(i, m)
    {
        rep(j, n)
        {
            char c1 = a[-player[2 * j].second][i];
            char c2 = a[-player[2 * j + 1].second][i];
            if (c1 == c2)
                continue;
            if ((c1 == 'G' && c2 == 'C') || (c1 == 'C' && c2 == 'P') || (c1 == 'P' && c2 == 'G'))
            {
                player[2 * j].first++;
            }
            else
            {
                player[2 * j + 1].first++;
            }
        }
        sort(ALL(player), greater<P>());
    }

    vector<int> ans(2*n);

    rep(i, 2 * n)
    {
        cout << -player[i].second + 1 << endl;
    }

    return 0;
}