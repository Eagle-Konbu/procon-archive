#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define reps(i, n) for (ll i = 1; i <= (ll)(n); i++)
#define rrep(i, n) for (ll i = (ll)n - 1; i >= 0; i--)
#define rreps(i, n) for (ll i = (ll)n; i > 0; i--)

int main()
{
    int n;
    cin >> n;
    vector<int> s(n);
    rep(i, n) cin >> s[i];

    int ans = 0;
    rep(i, n)
    {
        bool correct = false;
        reps(a, s[i]) reps(b, s[i])
        {
            int area = 4 * a * b + 3 * a + 3 * b;
            if(area == s[i]) correct = true;
        }

        if(!correct) ans++;
    }

    cout << ans << endl;
}
