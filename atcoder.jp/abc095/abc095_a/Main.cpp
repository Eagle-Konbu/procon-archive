#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (int)(n); i++)

int main()
{
    string s;
    cin >> s;

    int ans = 700;
    rep(i, 3) {
        if (s[i] == 'o') ans += 100;
    }

    cout << ans << endl;
}