use std::collections::HashSet;

use proconio::input;

fn main() {
    input! {
        n:usize,
    };

    let mut name_set = HashSet::new();

    for _ in 0..n {
        input! {
            s:String,
            t:String
        };

        name_set.insert(format!("{} {}", s,t));
    }

    if name_set.len() == n {
        println!("No");
    } else {
        println!("Yes")
    }
}
