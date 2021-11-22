#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define reps(i, n) for (ll i = 1; i <= (ll)(n); i++)
#define rrep(i, n) for (ll i = (ll)n - 1; i >= 0; i--)
#define rreps(i, n) for (ll i = (ll)n; i > 0; i--)

int main()
{
    ll n = 1048576;
    ll q;
    cin >> q;

    vector<ll> a(n, -1);
    set<ll> se;
    rep(i, n) se.insert(i);

    rep(i, q)
    {
        ll t, x;
        cin >> t >> x;
        if (t == 1)
        {
            auto it = se.lower_bound(x % n);
            if(it == se.end()) it = se.begin();
            a[*it] = x;
            se.erase(it);
        }
        else
        {
            cout << a[(x % n)] << endl;
        }
    }

    return 0;
}
