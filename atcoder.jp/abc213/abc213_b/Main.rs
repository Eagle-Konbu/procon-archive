use itertools::Itertools;
use proconio::input;

fn main() {
    input! {
        n:usize,
        a:[i32;n]
    };

    let mut x = Vec::new();

    for &a_tmp in a.iter().sorted() {
        x.push(a_tmp);
    }

    let booby = x[n - 2];

    let mut idx = 0;

    for i in 0..n {
        if a[i] == booby {
            idx = i;
        }
    }

    println!("{}", idx+1);
}
