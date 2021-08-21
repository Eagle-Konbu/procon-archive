use proconio::input;

fn main() {
    input!{
        n:i128
    };

    // let ans = n.log2();
    // println!("{}", &ans);
    let mut ans = 0;
    for k in 1..=60 {
        let tmp = 2_i128.pow(k);
        if tmp > n {
            break;
        }
        ans = k;
    }
    println!("{}", ans);
}
