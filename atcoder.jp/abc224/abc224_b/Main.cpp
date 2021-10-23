#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

int main()
{
    int a[50][50];
    int h, w;
    cin >> h >> w;
    rep(i, h)
    {
        rep(j, w) cin >> a[i][j];
    }

    for (int i1 = 0; i1 < h - 1; i1++)
    {
        for (int i2 = i1 + 1; i2 < h; i2++)
        {
            for (int j1 = 0; j1 < w - 1; j1++)
            {
                for (int j2 = j1 + 1; j2 < w; j2++)
                {
                    if (a[i1][j1] + a[i2][j2] > a[i2][j1] + a[i1][j2])
                    {
                        cout << "No" << endl;
                        return 0;
                    }
                }
            }
        }
    }

    cout << "Yes" << endl;

    return 0;
}