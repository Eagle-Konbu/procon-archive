#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (int)(n); i++)

int main()
{
    int n;
    set<string> items;

    cin >> n;
    rep(i, n) {
        string s;
        cin >> s;
        items.insert(s);
    }

    cout << items.size() << endl;

    return 0;
}