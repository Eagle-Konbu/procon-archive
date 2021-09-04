use proconio::input;

fn main() {
    input! {
        num:f32
    };

    let x = num.floor() as i32;

    let y = (num * 10.0) as i32 - x * 10;

    if y >= 0 && y <= 2 {
        println!("{}-",x);
    } else if y <= 6 {
        println!("{}",x);
    } else {
        println!("{}+",x);
    }
}
