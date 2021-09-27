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
    rep(i, 1 << n)
    {
        string str = "";
        for (int j = n - 1; j >= 0; j--)
        {
            if ((i & (1 << j)) == 0)
                str += "(";
            else
                str += ")";
        }
        int cnt = 0;
        bool judge;
        rep(i, n)
        {
            if (str[i] == '(')
                cnt++;
            else
                cnt--;
            if (cnt < 0)
            {
                judge = false;
                break;
            }
        }
        if (cnt == 0)
            judge = true;
        else
            judge = false;
        if (judge)
        {
            cout << str << endl;
        }
    }

    return 0;
}