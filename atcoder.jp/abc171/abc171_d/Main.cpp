#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
typedef pair<ll, ll> P;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define N_MAX 100000

int main()
{
    ll n;
    cin >> n;
    ll cnt[N_MAX + 1] = {};
    ll sum = 0;

    rep(i, n)
    {
        ll a;
        cin >> a;
        cnt[a]++;
        sum += a;
    }

    ll q;
    cin >> q;

    rep(i, q)
    {
        ll b, c;
        cin >> b >> c;

        sum -= b * cnt[b];
        sum += c * cnt[b];

        cnt[c] += cnt[b];
        cnt[b] = 0;

        cout << sum << endl;
    }

    return 0;
}