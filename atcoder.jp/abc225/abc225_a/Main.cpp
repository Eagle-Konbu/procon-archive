#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define reps(i, n) for (ll i = 1; i <= (ll)(n); i++)
#define rrep(i, n) for (ll i = (ll)n - 1; i >= 0; i--)
#define rreps(i, n) for (ll i = (ll)n; i > 0; i--)
#define ALL(x) (x).begin, (x).end
#define pb push_back


int main()
{
    string s;
    cin >> s;

    set<char> se;
    rep(i,3) se.insert(s[i]);

    int n = se.size();

    if (n == 1) cout << 1 << endl;
    else if (n == 2) cout << 3 << endl;
    else cout << 6 << endl;

    return 0;
}