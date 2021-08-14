use proconio::input;

fn main() {
    input! {
        n:u32
    };

    if n <= 125 {
        println!("4");
    } else if n <= 211 {
        println!("6");
    } else {
        println!("8");
    }
}
