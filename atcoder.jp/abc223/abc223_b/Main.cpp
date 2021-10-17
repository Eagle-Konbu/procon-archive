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
    string s;
    cin >> s;

    set<string> set;

    auto s_tmp = s;
    rep(i, s.length())
    {
        char s0 = s_tmp[0];
        for (int j = 1; j < (int)s.length(); j++)
        {
            s_tmp[j - 1] = s_tmp[j];
        }
        s_tmp[s.length() - 1] = s0;
        set.insert(s_tmp);
    }

    auto first = *set.begin();
    auto last = set.end();
    last--;

    cout << *set.begin() << endl
         << *last << endl;

    return 0;
}