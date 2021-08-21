use proconio::input;

fn main() {
    input! {
        s:String
    };

    if s == "Hello,World!".to_string() {
        println!("AC");
    } else {
        println!("WA");
    }
}
