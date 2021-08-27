use proconio::input;
fn main() {
    input! {
        s:String
    };

    for i in 0..3 {
        if s.chars().nth(i) == s.chars().nth(i+1) {
            println!("Bad");
            return;
        }
    }
    println!("Good");
}
