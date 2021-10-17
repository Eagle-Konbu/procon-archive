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

int main()
{
    int n;
    cin >> n;
    vector<P> ab;
    rep(i, n)
    {
        int a, b;
        cin >> a >> b;
        ab.pb(make_pair(a, b));
    }

    vector<double> length_arr(n, 0);
    rep(i, n) length_arr[i] = (double)ab[i].first / ab[i].second;

    double length_sum = 0;
    rep(i, n) length_sum += length_arr[i];

    double tmp = 0;
    int meet_idx = 0;
    rep(i, n)
    {
        tmp += length_arr[i];
        if (tmp >= length_sum / 2)
        {
            meet_idx = i;
            break;
        }
    }

    double x = 0;
    rep(i, meet_idx) x += length_arr[i];
    double sub = (length_sum / 2 - x) * ab[meet_idx].second;

    double ans = 0;
    rep(i, meet_idx) ans += ab[i].first;
    ans += sub;

    cout << ans << endl;

    return 0;
}