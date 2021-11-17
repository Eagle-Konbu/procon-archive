#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define reps(i, n) for (ll i = 1; i <= (ll)(n); i++)
#define rrep(i, n) for (ll i = (ll)n - 1; i >= 0; i--)
#define rreps(i, n) for (ll i = (ll)n; i > 0; i--)

int main()
{
    int n;
    cin >> n;
    vector<int> cnt(n + 1);
    rep(i, n)
    {
        int a;
        cin >> a;
        cnt[a]++;
    }

    int x = 0, y = 0;
    reps(i, n)
    {
        if (cnt[i] == 0)
            x = i;
        else if (cnt[i] == 2)
            y = i;
    }

    if (x == 0 && y == 0)
        cout << "Correct" << endl;
    else
        cout << y << " " << x << endl;

    return 0;
}