#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
typedef pair<ll, ll> P;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define reps(i, n) for (ll i = 1;; i <= (ll)(n); i++)
#define rrep(i, n) for (ll i = ((ll)(n)-1); i >= 0; i--)
#define rreps(i, n) for (ll i = ((ll)(n)); i > 0; i--)
#define ALL(x) (x).begin(), (x).end()
#define pb push_back

int main()
{
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n);
    rep(i, n + 1) cin >> a[i];
    rep(i, n) cin >> b[i];

    ll ans = 0;

    rep(i, n)
    {
        int beaten = min(a[i], b[i]);
        a[i] -= beaten;

        if (beaten < b[i])
        {
            int additional = min(b[i] - beaten, a[i + 1]);
            beaten += additional;
            a[i + 1] -= additional;
        }

        ans += beaten;
    }

    cout << ans << endl;

    return 0;
}