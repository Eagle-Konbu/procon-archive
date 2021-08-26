use proconio::input;

fn gcd(x: i64, y: i64) -> i64 {
    if y == 0 {
        x
    } else {
        gcd(y, x % y)
    }
}

fn lcm(x: i64, y: i64) -> i64 {
    let g = gcd(x, y);
    return x * y / g;
}

fn main() {
    input! {
        a:i64,b:i64,c:i64,d:i64
    };

    let mut cnt = 0;

    cnt += b / c;
    cnt += b / d;
    cnt -= b / lcm(c, d);

    cnt -= (a - 1) / c;
    cnt -= (a - 1) / d;
    cnt += (a - 1) / lcm(c, d);

    println!("{}", (b - a + 1) - cnt);
}
