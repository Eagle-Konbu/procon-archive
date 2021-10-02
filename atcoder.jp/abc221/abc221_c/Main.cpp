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
    string n;
    cin >> n;

    sort(ALL(n));

    ll ans = 0;

    do
    {
        rep(i, n.length() - 1)
        {
            auto left_s = n.substr(0, i + 1);
            auto right_s = n.substr(i + 1);
            if (right_s[0] == '0')
                continue;

            int left = stoi(left_s);
            int right = stoi(right_s);

            ll tmp = left * right;
            if (tmp > ans)
                ans = tmp;
        }
    } while (next_permutation(ALL(n)));
    cout << ans << endl;

    return 0;
}