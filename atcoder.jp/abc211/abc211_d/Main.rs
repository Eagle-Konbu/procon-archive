use proconio::input;

use std::collections::VecDeque;

fn main() {
    input! {
        n:usize,
        m:usize,
        ab:[(usize,usize);m]
    }

    let mut g = vec![vec![]; n];

    for &(a, b) in ab.iter() {
        g[a - 1].push(b - 1);
        g[b - 1].push(a - 1);
    }

    let mut dist = vec![std::i32::MAX; n];
    let mut cnt = vec![0; n];

    let mut q = VecDeque::new();

    q.push_back(0);
    dist[0] = 0;
    cnt[0] = 1;

    while q.len() != 0 {
        let v = q.pop_front().unwrap();

        for &u in g[v].iter() {
            if dist[u] == std::i32::MAX {
                dist[u] = dist[v] + 1;
                q.push_back(u);
                cnt[u] = cnt[v];
            } else if dist[u] == dist[v] + 1 {
                cnt[u] += cnt[v];
                cnt[u] %= 1_000_000_007;
            }
        }
    }

    println!("{}", cnt[n - 1]);
}
