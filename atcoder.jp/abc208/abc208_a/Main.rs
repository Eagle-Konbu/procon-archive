use proconio::input;

fn main() {
    input! {
        a:i32,
        b:i32
    };

    if a <= b && b <= 6 * a {
        println!("Yes");
    } else {
        println!("No");
    }
}
