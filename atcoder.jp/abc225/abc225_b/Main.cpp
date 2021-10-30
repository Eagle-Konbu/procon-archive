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
    int n;
    cin >> n;
    vector<vector<int>> g(n);


    rep(i, n - 1)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].pb(b);
        g[b].pb(a);
    }

    rep(i, n) {
        if((int)g[i].size() == n - 1) {
            cout << "Yes" << endl;
            return 0;
        }
        
    }

    cout << "No" << endl;

    return 0;
}