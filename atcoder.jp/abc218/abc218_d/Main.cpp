#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> p(n);
    rep(i, n) cin >> p[i].first >> p[i].second;
    sort(p.begin(), p.end());
    int ans = 0;

    rep(i, n)
    {
        rep(j, n)
        {
            if (p[i].first < p[j].first && p[i].second < p[j].second)
            {
                if (binary_search(p.begin(), p.end(), make_pair(p[i].first, p[j].second)) && binary_search(p.begin(), p.end(), make_pair(p[j].first, p[i].second)))
                    ans++;
            }
        }
    }

    cout << ans << endl;

    return 0;
}