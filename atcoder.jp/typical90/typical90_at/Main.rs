use proconio::input;

fn main() {
    input! {
        n:usize,
        a:[i32;n],
        b:[i32;n],
        c:[i32;n]
    };

    let mut num_list = Vec::new();
    for i in 0..46 {
        for j in 0..46 {
            for k in 0..46 {
                if (i + j + k) % 46 == 0 {
                    num_list.push((i, j, k));
                }
            }
        }
    }

    let mut ans = 0;
    for &(i, j, k) in num_list.iter() {
        let a_cnt = a.iter().filter(|&x| *x % 46 == i).count();
        let b_cnt = b.iter().filter(|&x| *x % 46 == j).count();
        let c_cnt = c.iter().filter(|&x| *x % 46 == k).count();

        ans += a_cnt * b_cnt * c_cnt;
    }

    println!("{}", &ans);
}
