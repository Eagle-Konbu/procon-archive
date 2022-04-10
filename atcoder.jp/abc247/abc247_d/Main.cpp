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
    int q;
    cin >> q;

    deque<P> deq;

    rep(i, q)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int x, c;
            cin >> x >> c;
            deq.push_back({x, c});
        }
        else
        {
            ll ans = 0;
            int c;
            cin >> c;
            int current_cnt = 0;
            while (current_cnt < c)
            {
                P front = deq.front();
                deq.pop_front();

                int front_num = front.first, front_cnt = front.second;
                int cnt_to_remove = c - current_cnt;
                ans += (ll)front_num * (ll)min(front_cnt, cnt_to_remove);
                if (front_cnt > cnt_to_remove)
                    deq.push_front({front_num, front_cnt - cnt_to_remove});
                current_cnt += min(front_cnt, cnt_to_remove);
            }
            cout << ans << endl;
        }
    }

    return 0;
}