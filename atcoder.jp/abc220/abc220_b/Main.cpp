#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
typedef pair<ll, ll> P;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

int main()
{
    int k;
    string a, b;
    cin >> k;
    cin >> a >> b;

    ll ans = 0;

    ll a_num = 0, b_num = 0;

    rep(i, a.length())
    {
        a_num += (a[i] - '0') * pow(k, a.length() - i - 1);
    }

    rep(i, b.length())
    {
        b_num += (b[i] - '0') * pow(k, b.length() - i - 1);
    }

    ans = a_num * b_num;

    cout << ans << endl;

    return 0;
}