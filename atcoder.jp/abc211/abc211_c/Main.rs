use proconio::input;

fn main() {
    input! {
        s:String
    };

    let s: Vec<char> = s.chars().collect();
    let t: Vec<char> = String::from("chokudai").chars().collect();
    let n = s.len();
    let mut dp = vec![vec![0; 9]; n + 1];

    for i in 0..=n {
        dp[i][0] = 1;
    }

    for i in 1..=n {
        for j in 1..=8 {
            if s[i - 1] != t[j - 1] {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
                dp[i][j] %= 1_000_000_007;
            }
        }
    }

    println!("{}", dp[n][8]);
}
