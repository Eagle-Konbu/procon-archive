use proconio::input;

fn main() {
    input! {
        a:i128, b:i128, c:i128, k:i128
    };

    let mut x = a-b;
    if k % 2 == 1 {
        x = -x;
    }

    println!("{}", x);
}
