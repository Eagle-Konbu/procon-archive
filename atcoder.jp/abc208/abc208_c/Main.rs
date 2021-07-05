use itertools::Itertools;
use proconio::input;

fn main() {
    input! {
        n: usize,
        mut k:usize,
        a:[usize; n]
    };

    let index_list = (0..n).sorted_by_key(|&i| a[i]).collect_vec();
    let mut ans_list = vec![0; n];

    for &i in index_list.iter().take(n) {
        ans_list[i] = k / n;
    }
    k %= n;

    for &i in index_list.iter().take(k) {
        ans_list[i] += 1;
    }

    println!("{}", ans_list.iter().map(|i| i).join("\n"));
}