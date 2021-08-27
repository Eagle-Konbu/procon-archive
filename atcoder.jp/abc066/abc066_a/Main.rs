use itertools::Itertools;
use proconio::input;
fn main() {
    input! {
        a:i32, b:i32, c:i32
    };

    let list: Vec<i32> = vec![a, b, c].into_iter().sorted().collect();

    println!("{}", list[0]+list[1]);
}
