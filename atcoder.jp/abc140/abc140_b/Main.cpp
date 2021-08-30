#include<bits/stdc++.h>
#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;
using ll = long long;
using P = pair<int, int>;

int main()
{
    int n;
    vector<int> a, b, c;

    cin >> n;

    rep(i, n) {
        int x;
        cin >> x;
        a.push_back(x-1);
    }
    rep(i,n) {
        int x;
        cin >> x;
        b.push_back(x);
    }
    rep(i,n-1) {
        int x;
        cin >> x;
        c.push_back(x);
    }

    int ans = 0;

    rep(i,n) {
        ans += b[a[i]];
    }

    rep(i, n-1) {
        if (a[i+1] == a[i] + 1) {
            ans += c[a[i]];
        }
    }

    cout << ans << endl;
}
