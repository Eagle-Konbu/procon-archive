#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (int)(n); i++)

int main()
{
    int a, b;
    cin >> a >> b;

    if (b % a == 0) cout << a + b << endl;
    else cout << b - a << endl;
}