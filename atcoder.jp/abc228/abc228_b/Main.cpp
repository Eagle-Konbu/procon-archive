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
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    vector<bool> knows(n + 1, false);
    rep(i, n) cin >> a[i];

    int cnt = 0;

    while (true)
    {
        if (!knows[x])
        {
            knows[x] = true;
            cnt++;
            x = a[x-1];
        }
        else {
            break;
        }
    }

    cout << cnt << endl;

    return 0;
}
