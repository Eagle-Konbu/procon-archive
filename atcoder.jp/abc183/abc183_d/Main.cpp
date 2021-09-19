#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
typedef pair<ll, ll> P;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

int main()
{
    int n, w;
    vector<P> events;
    cin >> n >> w;

    rep(i, n)
    {
        int s, t, p;
        cin >> s >> t >> p;

        events.push_back(make_pair(s, p));
        events.push_back(make_pair(t, -p));
    }

    sort(events.begin(), events.end());

    int used = 0;
    for (auto e : events)
    {
        used += e.second;
        if (used > w)
        {
            cout << "No" << endl;
            return 0;
        }
    }

    cout << "Yes" << endl;

    return 0;
}