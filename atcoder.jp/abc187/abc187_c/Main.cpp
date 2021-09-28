#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
typedef pair<ll, ll> P;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

int main()
{
    int n;
    cin >> n;
    set<string> normal, abnormal;
    rep(i, n)
    {
        string str;
        cin >> str;
        if (str[0] == '!')
            abnormal.insert(str);
        else
            normal.insert(str);
    }

    for (auto str : normal)
    {
        auto it = abnormal.find("!" + str);
        if (it != abnormal.end())
        {
            cout << str << endl;
            return 0;
        }
    }

    cout << "satisfiable" << endl;

    return 0;
}