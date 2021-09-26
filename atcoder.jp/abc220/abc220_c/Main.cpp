#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
typedef pair<ll, ll> P;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

int main()
{
    int n;
    ll x;
    cin >> n;
    vector<ll> a(n);
    rep(i, n) cin >> a[i];
    cin >> x;

    vector<ll> sums(n);
    sums[0] = a[0];
    for (int i = 1; i < n; i++)
    {
        sums[i] = a[i] + sums[i - 1];
    }

    ll cnt = x / sums[n - 1];
    x -= cnt * sums[n - 1];

    rep(i, n)
    {
        if (sums[i] > x)
        {
            cout << cnt * n + i + 1 << endl;
            return 0;
        }
    }

    return 0;
}