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
#define ERASE(x) x.erase(unique(x.begin(), x.end()), x.end())
#define POSL(x, v) (lower_bound(x.begin(), x.end(), v) - x.begin())
#define POSU(x, v) (upper_bound(x.begin(), x.end(), v) - x.begin())
#define all(x) x.begin(), x.end()

struct Edge
{
    ll to;
    ll weight;
    Edge(ll to, ll weight) : to(to), weight(weight) {}
};
typedef vector<vector<ll>> Graph;
typedef vector<vector<Edge>> WeightedGraph;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(m);
    vector<vector<int>> pos(n + 1);
    rep(i, m)
    {
        int k;
        cin >> k;
        rep(j, k)
        {
            int a_tmp;
            cin >> a_tmp;
            a[i].push_back(a_tmp);
        }
        rep(j, k)
        {
            pos[a[i][j]].push_back(i);
        }
    }

    vector<int> cnt(n + 1, 0);
    queue<int> q;
    rep(i, m)
    {
        cnt[a[i].back()]++;
    }
    reps(i, n) if (cnt[i] == 2) q.push(i);
    int take = 0;
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        take++;
        rep(i,2) {
            int p = pos[x][i];
            a[p].pop_back();
            if(a[p].size()){
                cnt[a[p].back()]++;
                if(cnt[a[p].back()]==2) q.push(a[p].back());
            }
        }
    }
    if(take == n) cout << "Yes" << endl;
    else cout << "No" << endl;

    return 0;
}