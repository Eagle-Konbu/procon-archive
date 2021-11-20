#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define reps(i, n) for (ll i = 1; i <= (ll)(n); i++)
#define rrep(i, n) for (ll i = (ll)n - 1; i >= 0; i--)
#define rreps(i, n) for (ll i = (ll)n; i > 0; i--)

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> scores(n, 0);
    rep(i, n)
    {
        int a, b, c;
        cin >> a >> b >> c;
        scores[i] = a + b + c;
    }

    vector<int> score_tmp(n, 0);
    rep(i, n) score_tmp[i] = scores[i];

    sort(score_tmp.begin(), score_tmp.end());
    reverse(score_tmp.begin(), score_tmp.end());
    int kth = score_tmp[k-1];

    rep(i,n) {
        if(kth - scores[i] <= 300) cout << "Yes" << endl;
        else cout << "No" << endl;
    }

    return 0;
}
