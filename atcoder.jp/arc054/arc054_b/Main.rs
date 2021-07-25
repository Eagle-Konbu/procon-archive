use proconio::input;

fn main() {
    input! {
        p:f64
    };

    let x = 1.5 * (p * 2.0f64.ln() / 1.5).log2();

    if x < 0f64 {
        println!("{}", p);
        return;
    }

    println!("{}", x + p * 2f64.powf(-x / 1.5));
}