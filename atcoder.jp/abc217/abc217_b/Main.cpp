#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (int)(n); i++)

int main()
{
    vector<string> s(3);
    cin >> s[0] >> s[1] >> s[2];

    bool abc=false, arc = false, agc = false, ahc = false;

    for(auto str: s) {
        if (str == "ABC") abc = true;
        else if (str == "ARC") arc = true;
        else if (str == "AGC") agc = true;
        else if (str == "AHC") ahc = true;
    }

    if (!abc) cout << "ABC";
    else if (!arc) cout << "ARC";
    else if (!agc) cout << "AGC";
    else if (!ahc) cout << "AHC";
    cout << endl;

    return 0;
}