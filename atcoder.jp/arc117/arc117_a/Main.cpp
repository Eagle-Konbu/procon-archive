#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

int main()
{
    int a, b;
    vector<int> e;
    cin >> a >> b;

    rep(i, a) e.push_back(i + 1);
    rep(i, b) e.push_back(-(i + 1));

    if (a > b)
    {
        ll sum = accumulate(e.begin(), e.end(), 0);
        e[a + b - 1] -= sum;
    }

    if (a < b)
    {
        ll sum = accumulate(e.begin(), e.end(), 0);
        e[a - 1] += -sum;
    }

    rep(i, a + b) cout << e[i] << " ";
    cout << endl;

    return 0;
}