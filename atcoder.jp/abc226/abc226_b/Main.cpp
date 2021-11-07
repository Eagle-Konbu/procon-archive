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
    // int a[200001][200001];
    // vector<int> l(n);
    // rep(i,n) {
    //     cin >> l[i];
    //     rep(j,l[i]) {
    //         cin >> a[i][j];
    //     }
    // }
    set<string> st;
    rep(i,n) {
        int l;
        string s, tmp;
        cin >> l;
        s = to_string(l);
        rep(j,l) {
            cin >> tmp;
            s += " " + tmp;
        }
        st.insert(s);
    }

    cout << st.size() << endl;

    return 0;
}