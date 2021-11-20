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
    int s,t,x;
    cin >> s >> t >> x;

    if (s >= t) t += 24;

    int on = 60 * s;
    int off = 60 * t;
    int target = 30 + 60 * x;
    int target2 = target + 24 * 60;

    if ((on <= target && target < off) || (on <= target2 && target2 < off)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}
