use proconio::input;

fn permutation(n: i128) -> i128 {
    if n == 0 || n == 1 {
        return 1;
    }
    return n * permutation(n - 1);
}

fn combination(a: i128, b: i128) -> i128 {
    return permutation(a) / (permutation(b) * permutation(a - b));
}

fn main() {
    input! {
        s:String
    };

    let mut used = 0;
    let mut not_used = 0;
    let mut unknown = 0;

    for i in 0..10 {
        let ch = s.chars().nth(i).unwrap();

        if ch == 'o' {
            used += 1;
        } else if ch == 'x' {
            not_used += 1;
        } else {
            unknown += 1;
        }
    }

    if used > 4 || unknown + not_used == 0 {
        println!("0");
        return;
    }

    let mut cnt = 0;
    for i in 0..=unknown {
        if used + i > 4 || used + i == 0 {
            continue;
        }

        let used_tmp = used + i;

        if used_tmp == 1 {
            cnt += combination(unknown, i);
        } else if used_tmp == 2 {
            cnt += (2 * 4 + combination(4, 2)) * combination(unknown, i);
        } else if used_tmp == 3 {
            cnt += (permutation(4) / permutation(2) * 3) * combination(unknown, i);
        } else {
            cnt += permutation(4) * combination(unknown, i);
        }
    }

    println!("{}", &cnt);
}
