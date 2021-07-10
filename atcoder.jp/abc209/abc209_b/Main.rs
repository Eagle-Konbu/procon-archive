use std::usize;

use itertools::Iterate;
use proconio::input;

fn main() {
    input! {
        n:usize,
        x:usize,
        a:[usize;n]
    };

    let mut sum = 0;
    for &item in a.iter() {
        sum += &item;
    }

    sum -= n / 2;
    
    if x >= sum {
        println!("Yes");
    } else {
        println!("No");
    }
}
