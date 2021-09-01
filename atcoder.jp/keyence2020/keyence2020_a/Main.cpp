#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (int)(n); i++)

int main()
{
    int h, w, n;
    cin >> h >> w >> n;

    int ans = 0;
    int cnt = 0;

    if (h >= w) {
        rep(i, w) {
            ans++;
            cnt += h;
            if (cnt >= n) break;
        }
    } else {
        rep(i, h) {
            ans++;
            cnt += w;
            if(cnt >= n) break;
        }
    }

    cout << ans << endl;
}