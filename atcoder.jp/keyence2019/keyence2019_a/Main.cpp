#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (int)(n); i++)

int main()
{
    vector<int> n(4);
    rep(i,4) {
        cin >> n[i];
    }

    sort(n.begin(), n.end());

    if (n[0] == 1 && n[1] == 4 && n[2] == 7 && n[3] == 9) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}