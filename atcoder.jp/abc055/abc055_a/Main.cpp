#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (int)(n); i++)

int main()
{
    int n;
    cin >> n;

    int x = 0, y = 0;

    rep(i, n){
        x += 800;
        if ((i + 1) % 15 == 0) y += 200;
    }

    cout << x - y << endl;
}