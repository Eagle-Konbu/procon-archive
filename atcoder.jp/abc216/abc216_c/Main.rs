use proconio::input;

fn main() {
    input! {
        mut n:i128
    };

    let mut magic_list = vec![];

    if n % 2 != 0 {
        n -= 1;
        magic_list.push("A");
    }

    while n > 1 {
        n /= 2;
        magic_list.push("B");
        while n % 2 != 0 {
            n -= 1;
            magic_list.push("A");
        }
    }

    if n == 1 {
        magic_list.push("A");
    }

    for s in magic_list.iter().rev() {
        print!("{}", &s);
    }
}