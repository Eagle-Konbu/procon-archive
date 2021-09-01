#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (int)(n); i++)

int main()
{
    int a,b;
    cin >> a >> b;

    if (a <= 5) {
        cout << 0 << endl;
    } else if (a <= 12) {
        cout << b / 2 << endl;
    } else {
        cout << b << endl;
    }

    return 0;
}