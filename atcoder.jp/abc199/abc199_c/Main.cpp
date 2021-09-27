#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
typedef pair<ll, ll> P;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

int main()
{
    int n, q;
    string s;
    cin >> n >> s >> q;

    string pre = s.substr(0, n), post = s.substr(n, n);

    rep(i, q)
    {
        int t, a, b;
        cin >> t >> a >> b;
        a--;
        b--;
        if (t == 1)
        {
            if (a < n && b < n)
            {
                swap(pre[a], pre[b]);
            }
            else if (a >= n && b >= n)
            {
                swap(post[a - n], post[b - n]);
            }
            else
            {
                swap(pre[a], post[b - n]);
            }
        }
        else
        {
            swap(pre, post);
        }
    }

    cout << pre + post << endl;

    return 0;
}