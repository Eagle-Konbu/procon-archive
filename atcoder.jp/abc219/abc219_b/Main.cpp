#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

int main()
{
    string s1, s2, s3, t;
    cin >> s1 >> s2 >> s3 >> t;

    rep(i, t.size()) { 
        if (t[i]=='1') cout << s1;
        else if (t[i]=='2') cout << s2;
        else if (t[i]=='3') cout << s3;
    }
    cout << endl;

    return 0;
}