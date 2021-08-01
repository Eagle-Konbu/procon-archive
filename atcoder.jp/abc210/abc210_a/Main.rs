use proconio::input;

fn main() {
    input! {
        n:u32,
        a:u32,
        x:u32,
        y:u32
    };

    let mut sum = 0;
    for i in 1..=n {
        if i <= a {
            sum += x;
        } else {
            sum += y;
        }
    }

    println!("{}", &sum);
}
