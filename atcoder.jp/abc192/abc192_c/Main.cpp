#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
typedef pair<ll, ll> P;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

ll f(ll n)
{
    string str = to_string(n);
    sort(str.begin(), str.end());
    ll g2 = stoll(str);
    reverse(str.begin(), str.end());
    ll g1 = stoll(str);

    return g1 - g2;
}

int main()
{
    int n, k;
    cin >> n >> k;
    ll a = n;
    rep(i, k) a = f(a);

    cout << a << endl;

    return 0;
}