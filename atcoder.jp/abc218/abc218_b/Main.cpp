#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

int main()
{
    vector<int> p(26);
    rep(i, 26) cin >> p[i];

    vector<char> alphabets;
    rep(i, 26) alphabets.push_back('a' + i);

    rep(i,26) {
        cout << alphabets[p[i]-1];
    }
    cout << endl;

    return 0;
}