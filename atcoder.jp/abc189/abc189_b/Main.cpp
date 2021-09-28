#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
typedef pair<ll, ll> P;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

int main()
{
    ll n, x;
    cin >> n >> x;

    ll cnt = 0;
    rep(i, n)
    {
        int v, p;
        cin >> v >> p;
        cnt += v * p;
        if(cnt > x * 100) {
            cout << i + 1 << endl;
            return 0;
        }
    }

    cout << -1 << endl;

    return 0;
}