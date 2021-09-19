#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
typedef pair<ll, ll> P;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

int main()
{
    string s;
    cin >> s;
    int n = s.size();

    if (n == 1)
    {
        if (stoi(s) % 8 == 0)
        {
            cout << "Yes" << endl;
            return 0;
        }
        cout << "No" << endl;
        return 0;
    }
    else if (n == 2)
    {
        if (stoi(s) % 8 == 0)
        {
            cout << "Yes" << endl;
            return 0;
        }
        swap(s[0], s[1]);
        if (stoi(s) % 8 == 0)
        {
            cout << "Yes" << endl;
            return 0;
        }
        cout << "No" << endl;
        return 0;
    }

    vector<int> cnt(10);
    for (auto x : s)
        cnt[x - '0']++;

    for (int i = 112; i < 1000; i += 8)
    {
        auto c = cnt;
        for (auto x : to_string(i))
            c[x - '0']--;
        if (all_of(c.begin(), c.end(), [](int x)
                   { return x >= 0; }))
        {
            cout << "Yes" << endl;
            return 0;
        }
    }

    cout << "No" << endl;

    return 0;
}