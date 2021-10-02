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
    string s, t;
    cin >> s >> t;

    if (s == t)
    {
        cout << "Yes" << endl;
        return 0;
    }

    rep(i, s.length() - 1)
    {
        auto tmp = s;
        swap(tmp[i], tmp[i + 1]);
        if (tmp == t)
        {
            cout << "Yes" << endl;
            return 0;
        }
    }

    cout << "No" << endl;

    return 0;
}