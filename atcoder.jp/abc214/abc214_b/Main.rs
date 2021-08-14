use proconio::input;

fn main() {
    input! {
        s:u128,
        t:u128,
    };

    let mut count = 0;

    for a in 0..=100 {
        for b in 0..=100 {
            for c in 0..=100 {
                if a * b * c <= t && a + b + c <= s {
                    count += 1;
                }
            }
        }
    }

    println!("{}", &count);
}
