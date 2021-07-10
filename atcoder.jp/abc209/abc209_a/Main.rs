use proconio::input;
use std::cmp::max;

fn main() {
    input! {
        a:i32,
        b:i32
    };

    println!("{}", max(b - a + 1, 0));
}
