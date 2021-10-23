#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

int main()
{
    string s;
    cin >> s;

    int n = s.length();

    if (s[n-1] == 'r') {
        cout << "er" << endl;
    } else {
        cout << "ist" << endl;
    }

    return 0;
}