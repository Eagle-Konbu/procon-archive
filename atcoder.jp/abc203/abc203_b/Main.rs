use std::io::stdin;

fn main() {
    let mut s = String::new();
    stdin().read_line(&mut s).ok();
    let (n, k): (i32, i32) = {
        let arr: Vec<&str> = s.split_whitespace().collect();
        (arr[0].parse().unwrap(), arr[1].parse().unwrap())
    };

    let mut ans = 0;
    for i in 0..n {
        for j in 0..k {
            let num = (i + 1) * 100 + j + 1;
            ans += num;
        }
    }

    println!("{}", ans);
}