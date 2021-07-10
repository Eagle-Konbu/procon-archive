use proconio::input;

fn main() {
    input! {
        n:usize,
        mut c:[usize;n]
    };

    c.sort();

    let mut ans:i128 = 1;

    for i in 0..n {
        ans *= (c[i] - i) as i128;
        ans %= ((10 as i32).pow(9) + 7) as i128;
    }

    println!("{}", &ans);
}
