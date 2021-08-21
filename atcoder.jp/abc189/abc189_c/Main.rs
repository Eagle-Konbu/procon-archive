use proconio::input;

fn main() {
    input! {
        n:usize,
        a:[i32;n]
    };

    let mut ans = 0;
    for l in 0..n {
        let mut x = a[l];
        for r in l..n {
            x = std::cmp::min(x, a[r]);
            ans = std::cmp::max(ans, x * ((r - l + 1) as i32));
        }
    }

    println!("{}", ans);
}
