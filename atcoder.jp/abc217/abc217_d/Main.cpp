#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
#define rep(i, n) for (ll i = 0; i < (int)(n); i++)

int main()
{
    int l, q;
    cin >> l >> q;
    vector<int> c(q), x(q);
    set<int> st;

    st.insert(0);
    st.insert(l);
    rep(i, q) cin >> c[i] >> x[i];
    rep(i, q) {
        if (c[i] == 1) st.insert(x[i]);
        if (c[i] == 2) {
            auto it = st.lower_bound(x[i]);
            cout << *it - *prev(it) << endl;
        }
    }

    return 0;
}