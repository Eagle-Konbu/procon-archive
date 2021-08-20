use proconio::input;
use std::cmp::min;
 
fn main() {
    input! {
        n:usize,
        s:[u128;n],
        t:[u128;n]
    };
 
    let mut time = min(t[n - 1] + s[n - 1], t[0]);
 
    let mut time_list = vec![time];
 
    for i in 1..n {
        time = min(time + s[i - 1], t[i]);
        time_list.push(time);
    }
 
    time = min(time + s[n - 1], t[0]);
    if time < time_list[0] {
        time_list[0] = time;
    }
 
    for i in 1..n {
        time = min(time + s[i - 1], t[i]);
        time_list[i] = time;
    }
 
    for &t_tmp in time_list.iter() {
        println!("{}", t_tmp);
    }
}