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
    int n, m;
    cin >> n >> m;

    dsu d(n);
    vector<ll> cnt(n);
    rep(i, m)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        if (d.same(a, b))
        {
            cout << "No" << endl;
            return 0;
        }
        d.merge(a, b);
        cnt[a]++;
        cnt[b]++;
    }

    rep(i, n)
    {
        if (cnt[i] > 2)
        {
            cout << "No" << endl;
            return 0;
        }
    }

    cout << "Yes" << endl;

    return 0;
}