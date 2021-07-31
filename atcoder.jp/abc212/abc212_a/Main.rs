use proconio::input;

fn main() {
    input! {
        a:u32,
        b:u32
    };

    if 0 < a && b == 0 {
        println!("Gold");
        return;
    } else if a == 0 && 0 < b {
        println!("Silver");
        return;
    } else {
        println!("Alloy");
        return;
    }
}
