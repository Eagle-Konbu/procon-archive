use proconio::input;

fn main() {
    input! {
        n:i128,
        a:i128,
        b:i128
    };

    let ans = (n / (a + b)) * a + std::cmp::min(a, n % (a + b));
    println!("{}", ans);
}
