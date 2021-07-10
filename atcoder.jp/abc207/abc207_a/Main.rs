use proconio::input;
use std::cmp;

fn main() {
    input! {
        a:usize,
        b:usize,
        c:usize
    };

    let max = cmp::max(cmp::max(a + b, a + c), b + c);
    println!("{}", &max);
}
