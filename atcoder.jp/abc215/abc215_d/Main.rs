use num_integer::Roots;
use proconio::input;
use std::collections::HashSet;

fn pfact(mut x: i32) -> Vec<i32> {
    let mut res = Vec::new();

    for i in 2..=x.sqrt() {
        while x % i == 0 {
            x /= i;
            res.push(i);
        }
    }

    if x != 1 {
        res.push(x);
    }

    res
}

fn main() {
    input! {
        n:usize,
        m:i32,
        a:[i32;n]
    };

    let mut ans = (1..=m).collect::<Vec<i32>>();
    let mut fact_set = HashSet::new();

    for &a_tmp in a.iter() {
        for &p in pfact(a_tmp).iter() {
            fact_set.insert(p);
        }
    }

    for &p in fact_set.iter() {
        ans = ans.clone().into_iter().filter(|&x| x % p != 0).collect()
    }

    println!("{}", ans.len());
    for &x in ans.iter() {
        println!("{}", x);
    }
}
