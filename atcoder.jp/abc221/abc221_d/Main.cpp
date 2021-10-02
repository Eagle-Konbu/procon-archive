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
    vector<P> x;
    int ans[200010] = {};
    int cnt = 0;

    rep(i, n)
    {
        int a, b;
        cin >> a >> b;
        x.pb({a, 1});
        x.pb({a + b, -1});
    }
    sort(ALL(x));

    rep(i, x.size() - 1)
    {
        cnt += x[i].second;
        ans[cnt] += (x[i + 1].first - x[i].first);
    }

    rep(i, n - 1) cout << ans[i + 1] << endl;
    cout << ans[n] << endl;

    return 0;
}