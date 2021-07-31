use proconio::input;

fn main() {
    input! {
        password:String
    };

    // let x1 = password.chars().nth(0);
    // let x2 = password.chars().
    let mut x = vec![0; 4];
    for i in 0..4 {
        x[i] = password.chars().nth(i).unwrap().to_string().parse().unwrap();
    }

    if x[0] == x[1] && x[1] == x[2] && x[2] == x[3] {
        println!("Weak");
        return;
    }

    for i in 0..3 {
        if x[i + 1] != ((x[i] + 1) % 10) {
            println!("Strong");
            return;
        }
    }

    println!("Weak");
}
