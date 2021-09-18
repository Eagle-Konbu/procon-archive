#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

int main()
{
    int x;
    
    cin >> x;

    if (x < 40)
        cout << 40 - x;
    else if (x < 70)
        cout << 70 - x;
    else if (x < 90)
        cout << 90 - x;
    else
        cout << "expert";

    cout << endl;

    return 0;
}