use proconio::input;

fn main() {
    input! {
        s:String
    };

    let res = s.parse::<u32>();

    if res.is_err() {
        println!("error");
    } else {
        let val = res.unwrap();
        println!("{}", &val * 2);
    }
}
