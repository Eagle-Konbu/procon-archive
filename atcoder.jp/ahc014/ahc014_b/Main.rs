#![allow(non_snake_case, unused_macros)]

use std::{
    collections::{BinaryHeap, VecDeque},
    env::args,
};

use proconio::input;
use rand::Rng;

const TIMELIMIT: f64 = 4.8;

fn main() {
    let timer = Timer::new();
    let args: Vec<String> = std::env::args().collect();

    let input = get_input();

    let initial_state = State::new(&input);

    // let (a, b, rand_min) = (
    //     args[1].parse::<f64>().unwrap(),
    //     args[2].parse::<f64>().unwrap(),
    //     args[3].parse::<f64>().unwrap(),
    // );

    // let (a, b, rand_min) = (0.15544107449517053, 3.8472453068245005, 0.08157176893051178);

    // let beam_width = (a * (input.N - 31) as f64 + b).round() as usize;

    // let ans = beam_search(&input, &initial_state, beam_width, rand_min);

    // let (chokudai_width, rand_min) = (
    //     args[1].parse::<usize>().unwrap(),
    //     args[2].parse::<f64>().unwrap(),
    // );
    let (chokudai_width, rand_min) = (2, 0.08);

    let ans = chokudai_search(&input, &initial_state, chokudai_width, rand_min);

    println!("{}", ans.len());
    for a in ans.iter() {
        for (x, y) in a.iter() {
            print!("{} {} ", x, y);
        }
        println!();
    }

    eprintln!("Score: {}", compute_score(&input, &ans).0);
    eprintln!("Time: {}", timer.get_time());
    // for optuna
    // println!("{}", compute_score(&input, &ans).0);
}

fn annealing_temperture(current_time: f64, t_0: f64, t_1: f64) -> f64 {
    let formalized_time = if current_time >= TIMELIMIT {
        1.0
    } else {
        current_time / TIMELIMIT
    };
    t_0.powf(1.0 - formalized_time) * t_1.powf(formalized_time)
}

fn manipulated_weight(original_weight: i32, rand_min: f64) -> i64 {
    let mut rng = rand::thread_rng();
    let rand = if rand_min == 1.0 {
        1.0
    } else {
        rng.gen_range(rand_min, 1.0)
    };
    (original_weight as f64 * rand * 1e8) as i64
}

fn chokudai_search(
    input: &Input,
    initial_state: &State,
    chokudai_width: usize,
    rand_min: f64,
) -> Output {
    let timer = Timer::new();

    let mut heaps = vec![BinaryHeap::new(); input.N * input.N + 1];

    heaps[0].push((compute_score(input, &[]).0, vec![]));

    let mut best_score = 0;
    let mut best_output = vec![];

    loop {
        if timer.get_time() > TIMELIMIT {
            break;
        }

        let mut max_t = 0;
        for t in 0..(input.N * input.N) {
            if timer.get_time() > TIMELIMIT {
                break;
            }
            for _ in 0..chokudai_width {
                if timer.get_time() > TIMELIMIT {
                    break;
                }
                if heaps[t].is_empty() {
                    break;
                }
                let (_, out) = heaps[t].pop().unwrap();

                let mut state = initial_state.clone();
                for &rect in out.iter() {
                    state.apply_move(rect);
                }

                let mut covered_points = input.ps.clone();
                for rect in out.iter() {
                    for &point in rect.iter() {
                        covered_points.push(point);
                    }
                }

                for i in 0..(input.N as i32 * input.N as i32) {
                    let new_point = (i % input.N as i32, i / input.N as i32);

                    if !state.has_point[new_point.0 as usize][new_point.1 as usize] {
                        let check_res = state.check_point(new_point);

                        for &r in check_res.iter() {
                            let mut new_out = out.clone();

                            new_out.push(r);

                            heaps[t + 1].push((
                                manipulated_weight(weight(r[0], input.N as usize), rand_min),
                                new_out.clone(),
                            ));
                        }
                    }
                    if timer.get_time() > TIMELIMIT {
                        break;
                    }
                }
                if timer.get_time() > TIMELIMIT {
                    break;
                }
            }
            if !heaps[t].is_empty() {
                max_t = t;
                // println!("{} {} {}", t, heaps[t].len(), timer.get_time());
            }
        }

        let (weight, out) = heaps[max_t].pop().unwrap();
        heaps[max_t].push((weight, out.clone()));
        let score = compute_score(input, &out).0;
        if score > best_score {
            best_score = score;
            best_output = out.clone();
        }
    }

    best_output
}

fn beam_search(input: &Input, initial_state: &State, beam_width: usize, rand_min: f64) -> Output {
    let timer = Timer::new();
    let mut rng = rand::thread_rng();

    let n = input.N as i32;

    let mut deq = VecDeque::new();
    deq.push_back(vec![]);

    let mut ans_heap = BinaryHeap::new();

    loop {
        if timer.get_time() >= TIMELIMIT {
            break;
        }
        let mut heap = BinaryHeap::new();

        if deq.is_empty() {
            break;
        }

        loop {
            if deq.is_empty() {
                break;
            }

            let out = deq.pop_front().unwrap();
            let mut state = initial_state.clone();

            for &rect in out.iter() {
                state.apply_move(rect);
            }

            for i in 0..(n * n) {
                let new_point = (i % input.N as i32, i / input.N as i32);

                if !state.has_point[new_point.0 as usize][new_point.1 as usize] {
                    let check_res = state.check_point(new_point);

                    for &r in check_res.iter() {
                        let mut new_out = out.clone();

                        new_out.push(r);

                        let rand_eff = rng.gen_range(rand_min, 1.0);

                        heap.push((
                            (weight(r[0], n as usize) as f64 * rand_eff * 1e8) as i64,
                            new_out,
                        ));
                    }
                }
                if timer.get_time() >= TIMELIMIT {
                    break;
                }
            }
            if timer.get_time() >= TIMELIMIT {
                break;
            }
        }
        eprintln!("{} {}", heap.len(), timer.get_time());
        for _ in 0..beam_width {
            if timer.get_time() >= TIMELIMIT {
                break;
            }
            if heap.is_empty() {
                break;
            }
            let (_, out) = heap.pop().unwrap();
            let score = compute_score(input, &out).0;
            ans_heap.push((score, out.clone()));
            deq.push_back(out.clone());
            if timer.get_time() >= TIMELIMIT {
                break;
            }
        }
    }

    ans_heap.pop().unwrap().1
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

#[macro_export]
macro_rules! mat {
	($($e:expr),*) => { Vec::from(vec![$($e),*]) };
	($($e:expr,)*) => { Vec::from(vec![$($e),*]) };
	($e:expr; $d:expr) => { Vec::from(vec![$e; $d]) };
	($e:expr; $d:expr $(; $ds:expr)+) => { Vec::from(vec![mat![$e $(; $ds)*]; $d]) };
}

pub const DXY: [(i32, i32); 8] = [
    (1, 0),
    (1, 1),
    (0, 1),
    (-1, 1),
    (-1, 0),
    (-1, -1),
    (0, -1),
    (1, -1),
];

pub type P = (i32, i32);
pub type Output = Vec<[P; 4]>;

#[derive(Clone, Debug)]
pub struct Input {
    pub N: usize,
    pub ps: Vec<P>,
}

impl std::fmt::Display for Input {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        writeln!(f, "{} {}", self.N, self.ps.len())?;
        for p in &self.ps {
            writeln!(f, "{} {}", p.0, p.1)?;
        }
        Ok(())
    }
}

fn get_input() -> Input {
    input! {
        N: usize, M: usize,
        ps: [(i32, i32); M]
    };
    Input { N, ps }
}

pub fn parse_input(f: &str) -> Input {
    let f = proconio::source::once::OnceSource::from(f);
    input! {
        from f,
        N: usize, M: usize,
        ps: [(i32, i32); M],
    }
    Input { N, ps }
}

#[derive(Clone, Debug, PartialEq, PartialOrd, Ord, Eq)]
pub struct State {
    pub has_point: Vec<Vec<bool>>,
    pub used: Vec<Vec<[bool; 8]>>,
}

impl State {
    pub fn new(input: &Input) -> Self {
        let mut has_point = mat![false; input.N; input.N];
        let used = mat![[false; 8]; input.N; input.N];
        for i in 0..input.ps.len() {
            has_point[input.ps[i].0 as usize][input.ps[i].1 as usize] = true;
        }
        Self { has_point, used }
    }
    pub fn check_move(&self, rect: [P; 4]) -> String {
        if let Some(i) = (1..4).find(|&i| !self.has_point[rect[i].0 as usize][rect[i].1 as usize]) {
            return format!("({}, {}) does not contain a dot", rect[i].0, rect[i].1);
        } else if self.has_point[rect[0].0 as usize][rect[0].1 as usize] {
            return format!("({}, {}) already contains a dot", rect[0].0, rect[0].1);
        } else {
            let dx01 = rect[1].0 - rect[0].0;
            let dy01 = rect[1].1 - rect[0].1;
            let dx03 = rect[3].0 - rect[0].0;
            let dy03 = rect[3].1 - rect[0].1;
            if dx01 * dx03 + dy01 * dy03 != 0
                || dx01 != 0 && dy01 != 0 && dx01.abs() != dy01.abs()
                || (rect[1].0 + dx03, rect[1].1 + dy03) != rect[2]
            {
                return "Illegal rectangle".to_owned();
            } else {
                for i in 0..4 {
                    let (mut x, mut y) = rect[i];
                    let (tx, ty) = rect[(i + 1) % 4];
                    let dx = (tx - x).signum();
                    let dy = (ty - y).signum();
                    let dir = (0..8).find(|&dir| DXY[dir] == (dx, dy)).unwrap();
                    while (x, y) != (tx, ty) {
                        if (x, y) != rect[i] && self.has_point[x as usize][y as usize] {
                            return format!("There is an obstacle at ({}, {})", x, y);
                        }
                        if self.used[x as usize][y as usize][dir] {
                            return "Overlapped rectangles".to_owned();
                        }
                        x += dx;
                        y += dy;
                        if self.used[x as usize][y as usize][dir ^ 4] {
                            return "Overlapped rectangles".to_owned();
                        }
                    }
                }
            }
        }
        String::new()
    }
    pub fn apply_move(&mut self, rect: [P; 4]) {
        self.has_point[rect[0].0 as usize][rect[0].1 as usize] = true;
        for i in 0..4 {
            let (mut x, mut y) = rect[i];
            let (tx, ty) = rect[(i + 1) % 4];
            let dx = (tx - x).signum();
            let dy = (ty - y).signum();
            // eprintln!("{:?} -> ({}, {})", rect, dx, dy);
            let dir = (0..8).find(|&dir| DXY[dir] == (dx, dy)).unwrap();
            while (x, y) != (tx, ty) {
                self.used[x as usize][y as usize][dir] = true;
                x += dx;
                y += dy;
                self.used[x as usize][y as usize][dir ^ 4] = true;
            }
        }
    }
    pub fn check_point(&self, new_point: P) -> Vec<[(i32, i32); 4]> {
        let dirs = [
            ((1, 0), (0, 1)),
            ((1, 0), (0, -1)),
            ((1, 1), (-1, 1)),
            ((1, 1), (1, -1)),
            ((0, 1), (1, 0)),
            ((0, 1), (-1, 0)),
            ((-1, 1), (1, 1)),
            ((-1, 1), (-1, -1)),
            ((-1, 0), (0, 1)),
            ((-1, 0), (0, -1)),
            ((-1, -1), (-1, 1)),
            ((-1, -1), (1, -1)),
            ((0, -1), (1, 0)),
            ((0, -1), (-1, 0)),
            ((1, -1), (1, 1)),
            ((1, -1), (-1, -1)),
        ];

        let n = self.has_point.len() as i32;

        let mut res = vec![];

        for &(dir1, dir2) in dirs.iter() {
            let (mut d1, mut d2) = (0, 0);
            let mut p = new_point;

            let (mut dir_idx1, mut dir_idx2) = (!0, !0);

            for (i, &dir) in DXY.iter().enumerate() {
                if dir == dir1 {
                    dir_idx1 = i;
                }
                if dir == dir2 {
                    dir_idx2 = i;
                }
            }

            loop {
                p.0 += dir1.0;
                p.1 += dir1.1;
                d1 += 1;

                if p.0 < 0 || p.0 >= n || p.1 < 0 || p.1 >= n {
                    d1 = -1;
                    break;
                }

                if self.has_point[p.0 as usize][p.1 as usize] {
                    break;
                }

                if self.used[p.0 as usize][p.1 as usize][dir_idx1]
                    || self.used[p.0 as usize][p.1 as usize][dir_idx1 ^ 4]
                {
                    d1 = -1;
                    break;
                }
            }
            p = new_point;

            loop {
                p.0 += dir2.0;
                p.1 += dir2.1;
                d2 += 1;

                if p.0 < 0 || p.0 >= n || p.1 < 0 || p.1 >= n {
                    d2 = -1;
                    break;
                }

                if self.has_point[new_point.0 as usize][p.1 as usize] {
                    break;
                }

                if self.used[new_point.0 as usize][p.1 as usize][dir_idx2]
                    || self.used[new_point.0 as usize][p.1 as usize][dir_idx2 ^ 4]
                {
                    d2 = -1;
                    break;
                }
            }

            if d1 == -1 || d2 == -1 {
                continue;
            }

            let rect = [
                new_point,
                (new_point.0 + d1 * dir1.0, new_point.1 + d1 * dir1.1),
                (
                    new_point.0 + d1 * dir1.0 + d2 * dir2.0,
                    new_point.1 + d1 * dir1.1 + d2 * dir2.1,
                ),
                (new_point.0 + d2 * dir2.0, new_point.1 + d2 * dir2.1),
            ];

            if !(rect[2].0 < 0 || rect[2].0 >= n || rect[2].1 < 0 || rect[2].1 >= n)
                && self.check_move(rect) == ""
            {
                res.push(rect);
            }
        }

        res
    }
    pub fn can_create_rect(&self, points: &[P; 3]) -> Result<[P; 4], String> {
        let (mut vec1, mut vec2, mut center_idx) = ((0, 0), (0, 0), !0);
        for i in 0..3 {
            let (e1, e2) = (
                (
                    points[(i + 1) % 3].0 - points[i].0,
                    points[(i + 1) % 3].1 - points[i].1,
                ),
                (
                    points[(i + 2) % 3].0 - points[i].0,
                    points[(i + 2) % 3].1 - points[i].1,
                ),
            );
            if e1.0 * e2.0 + e1.1 * e2.1 == 0 {
                vec1 = e1;
                vec2 = e2;
                center_idx = i;
                break;
            }
        }

        if center_idx == !0 {
            return Err("Not right angle".to_string());
        }

        let new_point = (
            points[center_idx].0 + vec1.0 + vec2.0,
            points[center_idx].1 + vec1.1 + vec2.1,
        );

        // if new_point is out of square
        if new_point.0 < 0
            || new_point.0 >= self.has_point.len() as i32
            || new_point.1 < 0
            || new_point.1 >= self.has_point.len() as i32
        {
            return Err("Out of square".to_string());
        }

        let rect = [new_point, points[2], points[1], points[0]];
        let check_res = self.check_move(rect);

        if check_res.is_empty() {
            Ok(rect)
        } else {
            Err(check_res)
        }
    }
}

pub fn weight((x, y): P, N: usize) -> i32 {
    let dx = x - N as i32 / 2;
    let dy = y - N as i32 / 2;
    dx * dx + dy * dy + 1
}

pub fn compute_score(input: &Input, out: &[[P; 4]]) -> (i64, String, State) {
    let mut state = State::new(input);
    for t in 0..out.len() {
        let err = state.check_move(out[t]);
        if !err.is_empty() {
            return (0, format!("{} (turn: {})", err, t), state);
        }
        state.apply_move(out[t]);
    }
    let mut num = 0;
    for &p in &input.ps {
        num += weight(p, input.N);
    }
    for rect in out {
        num += weight(rect[0], input.N);
    }
    let mut den = 0;
    for i in 0..input.N {
        for j in 0..input.N {
            den += weight((i as i32, j as i32), input.N);
        }
    }
    let score = (1e6 * (input.N * input.N) as f64 / input.ps.len() as f64 * num as f64 / den as f64)
        .round() as i64;
    (score, String::new(), state)
}
