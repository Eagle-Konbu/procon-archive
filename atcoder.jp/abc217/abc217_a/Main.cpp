#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (int)(n); i++)

int main()
{
    string s, t;
    cin >> s >> t;

    vector<string> list;
    list.push_back(s);
    list.push_back(t);

    sort(list.begin(), list.end());
    if (s == list[0]) cout << "Yes" << endl;
    else cout << "No" << endl;

    return 0;
}