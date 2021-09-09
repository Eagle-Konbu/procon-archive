#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
typedef modint1000000007 mint;

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    rep(i,n) cin >> a[i];
    a.push_back(0);
    sort(a.begin(),a.end());

    mint ans = 1;

    rep(i,n) ans *= a[i+1] - a[i] + 1;

    cout << ans.val() << endl;

    return 0;
}