use itertools::Itertools;
use proconio::input;

fn main() {
    input! {
        n:usize,
        mountains:[(String,u32);n]
    };

    let sorted:Vec<String> = mountains
        .into_iter()
        .sorted_by_key(|x| x.1)
        .rev()
        .map(|(name, _height)| name).collect();

    println!("{}", sorted[1]);
}
