use proconio::input;

fn combination(a: u128, b: u128) -> u128 {
    // return factorial(a) / (factorial(b) * factorial(a - b));
    let mut val = 1;

    for i in 0..b {
        val *= a - i;
        val /= i + 1;
    }

    return val;
}

fn main() {
    input! {
        l:u128
    };

    println!("{}", combination(l - 1, 11));
}
