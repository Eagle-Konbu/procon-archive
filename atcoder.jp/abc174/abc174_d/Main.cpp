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
    string stones;
    cin >> stones;

    int red_cnt = 0, white_cnt = 0;
    rep(i, n)
    {
        if (stones[i] == 'W')
            white_cnt++;
        else
            red_cnt++;
    }

    string final = "";
    rep(i, red_cnt) final += "R";
    rep(i, white_cnt) final += "W";

    int r2w = 0, w2r = 0;
    rep(i, n)
    {
        if (stones[i] != final[i])
        {
            if (stones[i] == 'R')
                r2w++;
            else if (stones[i] == 'W')
                w2r++;
        }
    }

    int swap_cnt = min(r2w, w2r);
    cout << r2w + w2r - swap_cnt << endl;

    return 0;
}