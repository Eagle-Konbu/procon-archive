#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

int main()
{
    string x;
    int n;
    cin >> x >> n;
    vector<string> s(n);
    vector<int> pos(26);

    rep(i, n) cin >> s[i];

    rep(i, 26)
    {
        pos[x[i] - 'a'] = i;
    }

    sort(begin(s), end(s), [&](const string &s, const string &t)
    {
        int len = min(s.size(), t.size());
        for (int i = 0; i < len; ++i)
        {
            if (s[i] != t[i])
            {
                return pos[s[i] - 'a'] < pos[t[i] - 'a'];
            }
        }
        return s.size() < t.size();
    });

    rep(i, n) cout << s[i] << endl;
}