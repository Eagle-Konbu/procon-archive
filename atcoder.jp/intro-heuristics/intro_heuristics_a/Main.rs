use proconio::input;
use rand::Rng;

const TIMELIMIT: f64 = 1.95;

fn main() {
    // let args: Vec<String> = std::env::args().collect();
    let mut timer = Timer::new();
    input! {
        d: usize,
        c: [i64; 26],
        s: [[i64; 26]; d]
    };

    let mut res = vec![];
    for _ in 0..d {
        let mut max_score = i64::min_value();
        let mut best_idx = 0;
        for i in 0..26 {
            res.push(i);
            let score = compute_score(&c, &s, &res);
            if max_score < score {
                max_score = score;
                best_idx = i;
            }
            res.pop();
        }
        res.push(best_idx);
    }

    // let T0: f64 = String::from(&args[1]).parse::<f64>().unwrap();
    // let T1: f64 = String::from(&args[2]).parse::<f64>().unwrap();
    const T0: f64 = 80339.4763873693;
    const T1: f64 = 24.58726000712244;

    let mut temperture = T0;

    let mut score = compute_score(&c, &s, &res);

    let mut time = timer.get_time();
    while time < TIMELIMIT {
        let d_rand = rand::thread_rng().gen_range(0, d);
        let t_rand = rand::thread_rng().gen_range(0, 26);

        let old_t = res[d_rand];
        res[d_rand] = t_rand;
        let new_score = compute_score(&c, &s, &res);

        let change = rand::thread_rng().gen_bool(p((new_score - score) as f64, temperture));
        if change {
            score = new_score;
        } else {
            res[d_rand] = old_t;
        }

        time = timer.get_time();
        temperture = T0.powf(1.0 - time / TIMELIMIT) * T1.powf(time / TIMELIMIT);
    }

    for &t in res.iter() {
        println!("{}", t + 1);
    }

    // println!("{}", 1000000 + score);
}

fn p(delta: f64, temperture: f64) -> f64 {
    if delta >= 0.0 {
        return 1.0;
    } else {
        return (delta / temperture).exp();
    }
}

fn compute_score(c: &Vec<i64>, s: &Vec<Vec<i64>>, out: &Vec<usize>) -> i64 {
    let mut score = 0;
    let mut last = vec![0; 26];

    for d in 0..out.len() {
        last[out[d]] = d + 1;
        for i in 0..26 {
            score -= (d + 1 - last[i]) as i64 * c[i];
        }
        score += s[d][out[d]];
    }

    return score;
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
