use std::mem::swap;

use proconio::{input, marker::*};
use rand::prelude::*;

const TIMELIMIT: f64 = 1.85;

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

fn main() {
    let input = parse_input();

    let mut res = String::new();
    let sol = genetic_algorithm(900, &input, 20);
    for &sol_item in sol.iter() {
        res = format!("{}{}", res, sol_item);
    }

    println!("{}", res);
}

fn genetic_algorithm(sol_size: usize, input: &Input, gen_size: usize) -> Output {
    let timer = Timer::new();

    let mut random = rand::thread_rng();
    let mut old_generation = vec![];

    let mut opt_solution = vec![0; 900];
    let mut opt_val = -1;

    for _ in 0..gen_size {
        let sol_tmp = (0..sol_size)
            .map(|_| random.gen_range(0, 4))
            .collect::<Vec<i32>>();
        old_generation.push(sol_tmp);
    }

    // let p1 = 0.02;
    let p2 = 0.8;

    let p1_min = 0.02;
    let p1_max = 0.2;

    let mut keep_cnt = 0;
    loop {
        let mut new_generation = vec![];
        loop {
            let p = random.gen::<f32>();
            let p1 = (p1_max - p1_min) / 10.0;
            if p < p1 {
                // 突然変異
                let mut x = old_generation[random.gen_range(0, gen_size)].clone();
                let idx = random.gen_range(0, sol_size);
                x[idx] = random.gen_range(0, 4);
                new_generation.push(x);
            } else if p < p2 {
                // 二点交叉
                let mut new_sol1 = vec![0; sol_size];
                let mut new_sol2 = vec![0; sol_size];
                let x1 = old_generation[random.gen_range(0, gen_size)].clone();
                let x2 = old_generation[random.gen_range(0, gen_size)].clone();

                let mut left = random.gen_range(0, sol_size + 1);
                let mut right = random.gen_range(0, sol_size + 1);
                if left > right {
                    swap(&mut left, &mut right);
                }

                for j in 0..sol_size {
                    if j < left || j > right {
                        new_sol1[j] = x1[j];
                        new_sol2[j] = x2[j];
                    } else {
                        new_sol1[j] = x2[j];
                        new_sol2[j] = x1[j];
                    }
                }
                new_generation.push(new_sol1);
                new_generation.push(new_sol2);
            } else {
                // 一つランダムにコピー
                let r = random.gen_range(0, gen_size);
                new_generation.push(old_generation[r].clone());
            }
            if new_generation.len() >= gen_size {
                break;
            }
        }

        let mut new_opt_val = -1;
        let mut new_opt_solution = vec![0; sol_size];

        for sol in new_generation.iter() {
            let val_tmp = compute_score(input, sol).0;

            if new_opt_val < val_tmp {
                new_opt_val = val_tmp;
                new_opt_solution = sol.clone();
            }
        }

        if opt_val < new_opt_val {
            opt_val = new_opt_val;
            opt_solution = new_opt_solution.clone();
            keep_cnt = 0;
        } else {
            keep_cnt += 1;
            if keep_cnt >= 10 {
                break;
            }
        }

        if timer.get_time() >= TIMELIMIT {
            return opt_solution;
        }
    }

    return opt_solution;
}

pub trait SetMinMax {
    fn setmin(&mut self, v: Self) -> bool;
    fn setmax(&mut self, v: Self) -> bool;
}
impl<T> SetMinMax for T
where
    T: PartialOrd,
{
    fn setmin(&mut self, v: T) -> bool {
        *self > v && {
            *self = v;
            true
        }
    }
    fn setmax(&mut self, v: T) -> bool {
        *self < v && {
            *self = v;
            true
        }
    }
}

#[macro_export]
macro_rules! mat {
	($($e:expr),*) => { Vec::from(vec![$($e),*]) };
	($($e:expr,)*) => { Vec::from(vec![$($e),*]) };
	($e:expr; $d:expr) => { Vec::from(vec![$e; $d]) };
	($e:expr; $d:expr $(; $ds:expr)+) => { Vec::from(vec![mat![$e $(; $ds)*]; $d]) };
}

pub type Output = Vec<i32>;

pub const N: usize = 30;
const DIJ: [(usize, usize); 4] = [(0, !0), (!0, 0), (0, 1), (1, 0)];

#[derive(Clone, Debug)]
pub struct Input {
    tiles: Vec<Vec<usize>>,
}

impl std::fmt::Display for Input {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        for i in 0..N {
            for j in 0..N {
                write!(f, "{}", self.tiles[i][j])?;
            }
            writeln!(f)?;
        }
        Ok(())
    }
}

pub fn parse_input() -> Input {
    input! {
        tiles: [Chars; N]
    }
    let tiles = tiles
        .iter()
        .map(|ts| ts.iter().map(|&c| (c as u8 - b'0') as usize).collect())
        .collect();
    Input { tiles }
}

pub fn parse_output(f: &str) -> Result<Vec<Output>, String> {
    let mut out = vec![];
    for line in f.lines() {
        let line = line.trim();
        let mut tmp = vec![];
        for c in line.chars() {
            if c < '0' || '3' < c {
                return Err(format!("Illegal output: {}", c));
            }
            tmp.push((c as u8 - b'0') as i32);
        }
        if tmp.len() != N * N {
            return Err(format!("Illegal output length: {}", line.len()));
        }
        out.push(tmp);
    }
    if out.len() == 0 {
        return Err(format!("empty output"));
    }
    Ok(out)
}

const ROTATE: [usize; 8] = [1, 2, 3, 0, 5, 4, 7, 6];

const TO: [[usize; 4]; 8] = [
    [1, 0, !0, !0],
    [3, !0, !0, 0],
    [!0, !0, 3, 2],
    [!0, 2, 1, !0],
    [1, 0, 3, 2],
    [3, 2, 1, 0],
    [2, !0, 0, !0],
    [!0, 3, !0, 1],
];

#[allow(arithmetic_overflow)]
pub fn compute_score(
    input: &Input,
    out: &Output,
) -> (i64, String, (Vec<Vec<usize>>, Vec<Vec<Vec<(i32, i32)>>>)) {
    let mut tiles = input.tiles.clone();
    for i in 0..N {
        for j in 0..N {
            for _ in 0..out[i * N + j] {
                tiles[i][j] = ROTATE[tiles[i][j]];
            }
        }
    }
    let mut ls = vec![];
    let mut used = mat![false; N; N; 4];
    let mut cycle = mat![(0, 0); N; N; 4];
    for i in 0..N {
        for j in 0..N {
            for d in 0..4 {
                if TO[tiles[i][j]][d] != !0 && !used[i][j][d] {
                    let mut i2 = i;
                    let mut j2 = j;
                    let mut d2 = d;
                    let mut length = 0;
                    let mut tmp = vec![];
                    while !used[i2][j2][d2] {
                        if TO[tiles[i2][j2]][d2] == !0 {
                            break;
                        }
                        length += 1;
                        used[i2][j2][d2] = true;
                        tmp.push((i2, j2, d2));
                        d2 = TO[tiles[i2][j2]][d2];
                        used[i2][j2][d2] = true;
                        tmp.push((i2, j2, d2));
                        i2 += DIJ[d2].0;
                        j2 += DIJ[d2].1;
                        if i2 >= N || j2 >= N {
                            break;
                        }
                        d2 = (d2 + 2) % 4;
                    }
                    if (i, j, d) == (i2, j2, d2) {
                        ls.push((length, tmp.clone()));
                        for (i, j, d) in tmp {
                            cycle[i][j][d].0 = length;
                        }
                    }
                }
            }
        }
    }
    let score = if ls.len() <= 1 {
        0
    } else {
        ls.sort();
        for &(i, j, d) in &ls[ls.len() - 1].1 {
            cycle[i][j][d].1 = 1;
        }
        for &(i, j, d) in &ls[ls.len() - 2].1 {
            cycle[i][j][d].1 = 2;
        }
        ls[ls.len() - 1].0 * ls[ls.len() - 2].0
    };
    (score as i64, String::new(), (tiles, cycle))
}
