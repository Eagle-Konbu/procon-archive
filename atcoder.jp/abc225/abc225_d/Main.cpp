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
    int n, q;
    cin >> n >> q;
    vector<ll> front(n + 1, -1), back(n + 1, -1);
    vector<vector<ll>> ans;

    rep(i, q)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            ll x, y;
            cin >> x >> y;
            back[x] = y;
            front[y] = x;
        }
        else if (t == 2)
        {
            ll x, y;
            cin >> x >> y;
            back[x] = -1;
            front[y] = -1;
        }
        else
        {
            ll x;
            cin >> x;
            while (front[x] != -1)
            {
                x = front[x];
            }
            vector<ll> ans_tmp;
            while (x != -1)
            {
                ans_tmp.pb(x);
                x = back[x];
            }
            ans.pb(ans_tmp);
        }
    }

    for (auto a : ans)
    {
        cout << a.size() << " ";
        for (auto i : a)
            cout << i << " ";
        cout << endl;
    }

    return 0;
}