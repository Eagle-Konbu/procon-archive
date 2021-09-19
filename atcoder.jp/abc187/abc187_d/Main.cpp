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
    cin >> n;
    vector<P> cities(n);
    ll x = 0;

    rep(i, n)
    {
        int a, b;
        cin >> a >> b;
        cities[i].first = a;
        cities[i].second = b;
        x -= a;
    }

    sort(cities.begin(), cities.end(), [](auto const &x, auto const &y)
         { return (x.first * 2 + x.second > y.first * 2 + y.second); });

    int cnt = 0;
    for (auto city : cities)
    {
        x += city.first * 2 + city.second;
        cnt++;
        if (x > 0)
            break;
    }

    cout << cnt << endl;

    return 0;
}