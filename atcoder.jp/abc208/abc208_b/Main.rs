use proconio::input;

fn factorial(n: i32) -> i32 {
    match n {
        0 => 1,
        1 => 1,
        _ => factorial(n - 1) * n,
    }
}

fn main() {
    input! {
        mut p:i32
    };

    let mut cnt = 0;

    for i in (1..=10).rev() {
        let cnt_tmp = p / factorial(i);
        p -= cnt_tmp * factorial(i);
        cnt += cnt_tmp
    }

    println!("{}", cnt)
}
