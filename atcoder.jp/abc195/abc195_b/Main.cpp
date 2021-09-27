#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
typedef pair<ll, ll> P;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

int main()
{
    int a, b, w;
    cin >> a >> b >> w;
    w *= 1000;

    int min_cnt = 1e9, max_cnt = 0;

    for (int n = 1; n <= 1000000; n++)
    {
        if (a * n <= w && w <= b * n)
        {
            min_cnt = min(min_cnt, n);
            max_cnt = max(max_cnt, n);
        }
    }
    if (max_cnt == 0)
    {
        cout << "UNSATISFIABLE" << endl;
        return 0;
    }

    cout << min_cnt << endl << max_cnt << endl;
    return 0;
}