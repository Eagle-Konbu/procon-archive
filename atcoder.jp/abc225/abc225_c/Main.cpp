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

int main()
{
    int n, m;
    cin >> n >> m;

    ll b[10000][7];
    rep(i, n) rep(j, m) cin >> b[i][j];

    int j0 = b[0][0] % 7;
    if (j0 == 0)
    {
        j0 = 7;
    }
    int i0 = (b[0][0] - j0) / 7 + 1;

    rep(i, n) rep(j, m)
    {
        if (j0 + j > 7)
        {
            cout << "No" << endl;
            return 0;
        }
        if (b[i][j] != ((i0 + i) - 1) * 7 + (j0 + j))
        {
            cout << "No" << endl;
            return 0;
        }
    }

    cout << "Yes" << endl;
    return 0;
}