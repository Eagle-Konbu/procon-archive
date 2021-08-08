use proconio::input;

fn main() {
    input! {
        a:i32,
        b:i32,
    };

    let c = a ^ b;

    println!("{}",&c);
}
