#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define reps(i, n) for (ll i = 1; i <= (ll)(n); i++)
#define rrep(i, n) for (ll i = (ll)n - 1; i >= 0; i--)
#define rreps(i, n) for (ll i = (ll)n; i > 0; i--)

int main()
{
    string s;
    cin >> s;

    vector<string> words;

    string tmp = "";
    for (char c : s)
    {
        tmp += c;
        if (c >= 'A' && c <= 'Z' && tmp.length() > 1)
        {
            tmp[0] += 'a' - 'A';
            tmp[tmp.length() - 1] += 'a' - 'A';
            words.push_back(tmp);
            tmp = "";
        }
    }

    sort(words.begin(), words.end());

    for (auto w : words)
        rep(i, w.length())
        {
            if (i == 0 || i == (ll)w.length() - 1)
            {
                w[i] += 'A' - 'a';
            }
            cout << w[i];
        }
    cout << endl;

    return 0;
}