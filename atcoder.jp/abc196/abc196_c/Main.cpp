#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
typedef pair<ll, ll> P;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

ll double_num(ll n)
{
    string str = to_string(n);
    return stoll(str + str);
}

int main()
{
    ll n;
    cin >> n;

    ll ans = 0;
    for (ll i = 1; double_num(i) <= n; i++)
    {
        ll num = double_num(i);
        if (num <= n)
            ans++;
    }

    cout << ans << endl;
}