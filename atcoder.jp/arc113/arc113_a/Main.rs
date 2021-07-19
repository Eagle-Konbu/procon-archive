use proconio::input;

fn main() {
    input! {
        k:i32,
    };

    let mut cnt = 0;

    for a in 1..=k {
        for b in 1..=k {
            if a*b > k {
                break;
            }
            cnt += k/(a*b);
        }
    }

    println!("{}",&cnt);
}