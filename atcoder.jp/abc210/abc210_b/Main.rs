use proconio::input;

fn main() {
    input! {
        n:usize,
        s:String
    };

    let x:Vec<char> = s.chars().collect();

    for i in 0..n {
        let is_bad = x[i] == '1';
        if is_bad {
            if i % 2 == 0 {
                println!("Takahashi");
                return;
            } else {
                println!("Aoki");
                return;
            }
        }
    }
}
