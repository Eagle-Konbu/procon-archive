#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
typedef pair<ll, ll> P;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
typedef modint1000000007 mint;

int main()
{
    ll n, k;
    cin >> n >> k;

    if (n == 1)
    {
        cout << mint(k).val() << endl;
        return 0;
    }

    if (n == 2)
    {
        mint ans = k * (k - 1);
        cout << ans.val() << endl;
        return 0;
    }

    mint ans = mint(k) * mint(k - 1) * mint(k - 2).pow(n - 2);

    cout << ans.val() << endl;

    return 0;
}