use proconio::input;
use std::collections::HashSet;

fn main() {
    input! {
        n:i128
    };

    // let mut cnt = 0;
    let mut ans_set = HashSet::new();
    for a in 2..=((n as f64).sqrt().floor() as i128) {
        let mut x = a * a;
        while x <= n {
            ans_set.insert(x);
            x *= a;
        }
    }

    println!("{}", n - (ans_set.len() as i128));
}
