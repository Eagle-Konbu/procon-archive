use std::io::stdin;

fn main() {
    let mut s = String::new();
    stdin().read_line(&mut s).ok();
    let (a, b, c) = {
        let arr: Vec<&str> = s.split_whitespace().collect();
        (arr[0], arr[1], arr[2])
    };

    let mut res = "0";
    if a == b {
        res = &c;
    } else if a == c {
        res = &b;
    } else if b == c {
        res = &a;
    }

    println!("{}", res);
}
