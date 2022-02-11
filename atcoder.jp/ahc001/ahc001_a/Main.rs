use proconio::input;
use rand::Rng;
use std::cmp::{max, min};

const TIME_LIMIT: f64 = 4.95;

fn main() {
    let args: Vec<String> = std::env::args().collect();
    let mut timer = Timer::new();

    input! {
        n:usize,
        xyr: [(i64,i64,i64); n]
    };
    let x = xyr.iter().map(|&a| a.0).collect::<Vec<_>>();
    let y = xyr.iter().map(|&a| a.1).collect::<Vec<_>>();
    let r = xyr.iter().map(|&a| a.2).collect::<Vec<_>>();

    let mut ab = vec![];
    let mut cd = vec![];

    for i in 0..n {
        ab.push((x[i], y[i]));
        cd.push((x[i] + 1, y[i] + 1));
    }

    let mut score = calculate_score(&ab, &cd, &x, &y, &r);

    let t_start: f64 = 9490.64592618072;
    let t_end: f64 = 0.04022541684308045;
    // let t_start = String::from(&args[1]).parse::<f64>().unwrap();
    // let t_end = String::from(&args[2]).parse::<f64>().unwrap();

    let size_min = 13;
    let size_max = 41;
    // let size_min = String::from(&args[1]).parse::<i64>().unwrap();
    // let size_max = String::from(&args[2]).parse::<i64>().unwrap();

    let mut temperature = t_start;
    while timer.get_time() < TIME_LIMIT {
        let rand_idx = rand::thread_rng().gen_range(0, n);
        let dir = rand::thread_rng().gen_range(0, 4);
        let size = rand::thread_rng().gen_range(size_min, size_max);
        // let size = 1;
        match dir {
            0 => cd[rand_idx].0 += size,
            1 => cd[rand_idx].1 += size,
            2 => ab[rand_idx].0 -= size,
            3 => ab[rand_idx].1 -= size,
            _ => (),
        };
        let new_score = calculate_score(&ab, &cd, &x, &y, &r);

        let change = rand::thread_rng().gen_bool(prob((new_score - score) as f64, temperature));
        if is_valid(&ab, &cd, n, rand_idx) && new_score > score {
            // println!("Score updated");
            score = new_score;
        } else {
            match dir {
                0 => cd[rand_idx].0 -= size,
                1 => cd[rand_idx].1 -= size,
                2 => ab[rand_idx].0 += size,
                3 => ab[rand_idx].1 += size,
                _ => (),
            }
        }
        temperature =
            t_start.powf(1.0 - timer.get_time() / TIME_LIMIT) * t_end.powf(timer.get_time());
    }

    for i in 0..n {
        println!("{} {} {} {}", ab[i].0, ab[i].1, cd[i].0, cd[i].1);
    }
    // println!("{}", score);
}

fn prob(delta: f64, temperature: f64) -> f64 {
    if delta >= 0.0 {
        return 1.0;
    } else {
        return (delta / temperature).exp();
    }
}

fn is_valid(ab: &Vec<(i64, i64)>, cd: &Vec<(i64, i64)>, n: usize, i: usize) -> bool {
    if ab[i].0 < 0 || ab[i].1 < 0 || cd[i].0 < 0 || cd[i].1 < 0 {
        return false;
    }
    if ab[i].0 > 10000 || ab[i].1 > 10000 || cd[i].0 > 10000 || cd[i].1 > 10000 {
        return false;
    }

    for j in 0..n {
        if i == j {
            continue;
        }
        if ab[i].0 < cd[j].0 && cd[i].0 > ab[j].0 && ab[i].1 < cd[j].1 && cd[i].1 > ab[j].1 {
            return false;
        }
    }

    return true;
}

fn calculate_score(
    ab: &Vec<(i64, i64)>,
    cd: &Vec<(i64, i64)>,
    x: &Vec<i64>,
    y: &Vec<i64>,
    r: &Vec<i64>,
) -> i64 {
    let n = ab.len();
    let mut p = vec![];
    for i in 0..n {
        if (ab[i].0 as f64 <= (x[i] as f64) + 0.5 && (x[i] as f64) + 0.5 <= cd[i].0 as f64)
            && (ab[i].1 as f64 <= (y[i] as f64) + 0.5 && (y[i] as f64) + 0.5 <= cd[i].1 as f64)
        {
            let width = (ab[i].0 - cd[i].0).abs();
            let height = (ab[i].1 - cd[i].1).abs();
            let s = width * height;
            p.push(1.0 - (1.0 - (min(r[i], s) as f64) / (max(r[i], s) as f64)).powf(2.0) as f64);
        } else {
            p.push(0.0);
        }
    }
    return (1000000000.0 * p.iter().sum::<f64>() / (n as f64)).round() as i64;
}

fn get_time() -> f64 {
    let t = std::time::SystemTime::now()
        .duration_since(std::time::UNIX_EPOCH)
        .unwrap();
    t.as_secs() as f64 + t.subsec_nanos() as f64 * 1e-9
}

struct Timer {
    start_time: f64,
}

impl Timer {
    fn new() -> Timer {
        Timer {
            start_time: get_time(),
        }
    }

    fn get_time(&self) -> f64 {
        get_time() - self.start_time
    }

    #[allow(dead_code)]
    fn reset(&mut self) {
        self.start_time = 0.0;
    }
}
