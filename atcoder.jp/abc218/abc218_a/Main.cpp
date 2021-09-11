#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

int main()
{
    int n;
    string s;
    cin >> n >> s;

    if (s[n-1] == 'o') {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}