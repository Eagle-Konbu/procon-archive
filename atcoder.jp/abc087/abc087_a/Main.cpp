#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (int)(n); i++)

int main()
{
    int x, a, b;
    cin >> x >> a >> b;

    x -= a;

    while(x - b >= 0) x -= b;

    cout << x << endl;
}