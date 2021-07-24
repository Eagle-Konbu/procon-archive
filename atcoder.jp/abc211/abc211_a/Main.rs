use proconio::input;

fn main() {
    input! {
        a:i32,
        b:i32
    };

    let c:f64 = ((a - b) as f64) / 3.0 + (b as f64);

    println!("{}",&c);
}
