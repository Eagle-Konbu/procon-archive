#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

int main()
{
    int n, m;
    cin >> n >> m;
    dsu d(n);
    rep(i, m)
    {
        int a, b;
        cin >> a >> b;
        d.merge(a - 1, b - 1);
    }

    cout << d.groups().size() - 1 << endl;

    return 0;
}