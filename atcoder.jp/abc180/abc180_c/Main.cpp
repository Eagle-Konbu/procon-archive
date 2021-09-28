#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
typedef pair<ll, ll> P;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

int main()
{
    ll n;
    cin >> n;
    set<ll> ans;

    for (ll i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            ans.insert(i);
            ans.insert(n / i);
        }
    }

    for (auto x : ans)
        cout << x << endl;

    return 0;
}