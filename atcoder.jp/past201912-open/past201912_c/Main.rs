use itertools::Itertools;
use proconio::input;

fn main() {
    input! {
        list:[u8;6]
    };

    let sorted_list: Vec<u8> = list.into_iter().sorted().rev().collect();

    println!("{}", sorted_list[2]);
}
