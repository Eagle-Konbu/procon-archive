use proconio::input;
fn main() {
    input! {
        x:i32
    };

    if x >= 0 {
        println!("{}", x);
    } else {
        println!("0");
    }
}
