use proconio::input;

fn main() {
    input! {
        n:usize,
        a:[u32;n]
    };

    for i in 0..(n - 1) {
        if a[i] == a[i + 1] {
            println!("stay");
        } else if a[i + 1] < a[i] {
            println!("down {}", a[i] - a[i + 1]);
        } else {
            println!("up {}", a[i + 1] - a[i]);
        }
    }
}
