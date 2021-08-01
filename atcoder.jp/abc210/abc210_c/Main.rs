use proconio::input;
use std::collections::HashMap;

fn main() {
    input! {
        n:usize,
        k:usize,
        c:[i32;n]
    };

    let mut mp = HashMap::<i32, i32>::new();

    for i in 0..k {
        *mp.entry(c[i]).or_insert(0) += 1;
    }
    let mut cnt = mp.len();

    for i in 0..(n - k) {
        *mp.entry(c[i + k]).or_insert(0) += 1;
        *mp.entry(c[i]).or_insert(0) -= 1;
        if mp[&c[i]] == 0 {
            mp.remove(&c[i]);
        }
        cnt = std::cmp::max(cnt, mp.len());
    }

    println!("{}", cnt);
}
