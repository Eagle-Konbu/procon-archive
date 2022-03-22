#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
typedef long long ll;
typedef pair<ll, ll> P;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define reps(i, n) for (ll i = 1; i <= (ll)(n); i++)
#define rrep(i, n) for (ll i = (ll)n - 1; i >= 0; i--)
#define rreps(i, n) for (ll i = (ll)n; i > 0; i--)
#define SORT(x) sort(x.begin(), x.end())
#define ERASE(x) x.erase(unique(x.begin(),x.end()),x.end())
#define POSL(x, v) (lower_bound(x.begin(),x.end(),v)-x.begin())
#define POSU(x, v) (upper_bound(x.begin(),x.end(),v)-x.begin())
#define all(x) x.begin(), x.end()

struct Edge {
    ll to;
    ll weight;
    Edge(ll to, ll weight) : to(to), weight(weight) {}
};
typedef vector<vector<ll>> Graph;
typedef vector<vector<Edge>> WeightedGraph;

int main()
{
    int n,q;
    cin >> n;
    vector<int> a(n);
    rep(i,n) cin >> a[i];
    cin >> q;

    SORT(a);
    rep(i,q) {
        int b;
        cin >> b;
        int idx = POSL(a,b);
        if(idx-1>=0) cout << min(abs(b - a[idx]), abs(b - a[idx - 1])) << endl;
        else cout << abs(b - a[idx]) << endl;
    }

    return 0;
}