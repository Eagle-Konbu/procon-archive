#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (int)(n); i++)

int main()
{
    int a,b,c;

    cin >> a >> b >> c;

    if (c - a + b < 0) {
        cout << 0 << endl;
    } else {
        cout << c - (a - b) << endl;
    }

    return 0;
}