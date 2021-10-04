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
    vector<P> p;
    rep(i, 2)
    {
        int x, y;
        cin >> x >> y;
        p.pb({x, y});
    }

    int x = p[1].first - p[0].first, y = p[1].second - p[0].second;
    cout << p[1].first - y << " " << p[1].second + x << " " << p[1].first - y - x << " " << p[1].second + x - y << endl;

    return 0;
}