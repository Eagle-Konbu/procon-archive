use proconio::{input, source::line::LineSource};
use rand::prelude::*;
use rand_distr::StandardNormal;
use std::io::{self, BufReader};

fn main() {
    let mut stdin = LineSource::new(BufReader::new(io::stdin()));
    macro_rules! input(($($tt:tt)*) => (proconio::input!(from &mut stdin, $($tt)*)));

    let mut rng = rand::thread_rng();

    input! {
        n:usize,
        m:usize,
        k:usize,
        r:usize,
        d: [[i32; k]; n],
        uv: [(usize, usize); r],
    };

    let input = Input { n, m, k, r, d, uv };
    let job_graph = input.job_graph();

    let s = expect_s(&input, &mut rng, 100000);

    let mut in_degs = vec![0; input.n];
    for v in 0..input.n {
        for &vv in job_graph[v].iter() {
            in_degs[vv] += 1;
        }
    }

    let mut jobs = (0..input.n)
        .map(|id| Job {
            id,
            in_progress: false,
            finished: false,
        })
        .collect::<Vec<Job>>();

    let mut members = (0..input.m)
        .map(|id| Member {
            id,
            in_progress: false,
            job_id_working_on: None,
        })
        .collect::<Vec<Member>>();

    loop {
        let mut allocations = vec![];
        for i in 0..members.len() {
            if members[i].in_progress {
                continue;
            }

            let pending_jobs_iter = jobs
                .iter()
                .filter(|&job| in_degs[job.id] == 0 && !job.in_progress && !job.finished);
            let mut pending_jobs = vec![];
            for &job in pending_jobs_iter {
                pending_jobs.push(job);
            }

            if pending_jobs.is_empty() {
                break;
            }
            let job = pending_jobs
                .iter()
                .min_by_key(|&j| expect_mh(&input, j, &s))
                .unwrap();

            allocations.push((members[i], job.clone()));

            members[i].in_progress = true;
            members[i].job_id_working_on = Some(job.id);
            jobs[job.id].in_progress = true;
        }

        print!("{} ", allocations.len());
        for &allocation in allocations.iter() {
            print!("{} {} ", allocation.0.id + 1, allocation.1.id + 1);
        }
        println!();

        input! {
            n:i32,
        };

        if n == -1 {
            break;
        }

        input! {
            f:[usize; n]
        };

        for &i in f.iter() {
            members[i - 1].in_progress = false;
            jobs[members[i - 1].job_id_working_on.unwrap()].finished = true;

            for &v in job_graph[members[i - 1].job_id_working_on.unwrap()].iter() {
                in_degs[v] -= 1;
            }
        }
    }
}

fn expect_mh(input: &Input, job: &Job, s: &Vec<i32>) -> i32 {
    let w = (0..input.k)
        .map(|k| std::cmp::max(0, input.d[job.id][k] - s[k]))
        .sum::<i32>();
    if w == 0 {
        return 1;
    } else {
        let mut res = 0;
        for r in -3..=3 {
            res += std::cmp::max(1, w + r);
        }
        return res / 7;
    }
}

fn expect_s(input: &Input, rng: &mut ThreadRng, simulation_cnt: usize) -> Vec<i32> {
    let mut s = vec![0.0; input.k];
    for _ in 0..simulation_cnt {
        let s_tmp = calc_s(input, rng);
        for i in 0..s_tmp.len() {
            s[i] += s_tmp[i];
        }
    }
    for i in 0..input.k {
        s[i] = (s[i] / simulation_cnt as f64).round()
    }
    return s.iter().map(|&x| x as i32).collect::<Vec<i32>>();
}

fn calc_s(input: &Input, rng: &mut ThreadRng) -> Vec<f64> {
    let s_prime = (0..input.k)
        .map(|_| rng.sample::<f64, _>(StandardNormal).abs())
        .collect::<Vec<f64>>();

    let s_sqare_sum = s_prime.iter().map(|&x| x * x).sum::<f64>();
    let s = (0..input.k)
        .map(|i| {
            let q = rng.gen_range(20.0, 60.0) / s_sqare_sum.sqrt();
            q * s_prime[i]
        })
        .collect::<Vec<f64>>();

    return s;
}

#[derive(Debug, Clone, Copy)]
struct Job {
    id: usize,
    in_progress: bool,
    finished: bool,
}

#[derive(Debug, Clone, Copy)]
struct Member {
    id: usize,
    in_progress: bool,
    job_id_working_on: Option<usize>,
}

struct Input {
    n: usize,
    m: usize,
    k: usize,
    r: usize,
    d: Vec<Vec<i32>>,
    uv: Vec<(usize, usize)>,
}

impl Input {
    fn job_graph(&self) -> Vec<Vec<usize>> {
        let mut g = vec![vec![]; self.n];
        for &(u, v) in self.uv.iter() {
            g[u - 1].push(v - 1);
        }

        return g;
    }
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
        self.start_time = get_time();
    }
}
