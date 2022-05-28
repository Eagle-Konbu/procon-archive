use proconio::{input, marker::*, source::Source};
use rand::prelude::*;
use std::{
    collections::{BTreeMap, BTreeSet},
    io::prelude::*,
};

const TIME_LIMIT: f64 = 1.9;

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
    let timer = Timer::new();

    let input = get_input();

    let mut current_position = Point::new(400, 400);

    let office_position = Point::new(400, 400);

    let mut orders = vec![];
    let mut positions = vec![(current_position.x, current_position.y)];

    let max_distance_from_office = (distance_threshold(&input) as f64 * 1.3) as i32;
    // let max_distance_from_office = 400;

    for _ in 0..50 {
        let mut next = !0;
        let mut min_distance = 10000;
        for i in 0..1000 {
            let distance_tmp =
                current_position.distance(&Point::new(input.from[i].0, input.from[i].1));
            if min_distance > distance_tmp
                && !orders.contains(&i)
                && office_position.distance(&Point::new(input.from[i].0, input.from[i].1))
                    <= max_distance_from_office
                && office_position.distance(&Point::new(input.to[i].0, input.to[i].1))
                    <= max_distance_from_office
            {
                next = i;
                min_distance = distance_tmp;
            }
        }
        orders.push(next);
        current_position = Point::new(input.from[next].0, input.from[next].1);
    }

    for &order in orders.iter() {
        positions.push((input.from[order].0, input.from[order].1));
    }

    let mut delivered = vec![false; 1000];
    for _ in 0..50 {
        let mut next = !0;
        let mut min_distance = 10000;
        for &i in orders.iter() {
            let distance_tmp = current_position.distance(&Point::new(input.to[i].0, input.to[i].1));
            if min_distance > distance_tmp && !delivered[i] {
                next = i;
                min_distance = distance_tmp;
            }
        }
        delivered[next] = true;
        positions.push((input.to[next].0, input.to[next].1));
        current_position = Point::new(input.to[next].0, input.to[next].1);
    }

    positions.push((400, 400));

    let mut output = Output {
        r: orders,
        path: positions,
    };

    annealing(&input, &mut output, 100.0, 0.1, &timer);
    output.print();

    // println!("");
}

fn distance_threshold(input: &Input) -> i32 {
    let mut min = 0;
    let mut max = 1000;

    let office_position = Point::new(400, 400);

    loop {
        let med = (min + max) / 2;
        let mut cnt = 0;
        for i in 0..1000 {
            if office_position.distance(&Point::new(input.from[i].0, input.from[i].1)) <= med
                && office_position.distance(&Point::new(input.to[i].0, input.to[i].1)) <= med
            {
                cnt += 1;
            }
        }
        if cnt >= 50 {
            max = med;
        } else {
            min = med;
        }

        if (max-min).abs() <= 1 {
            break;
        }
    }

    return max;
}

fn annealing(input: &Input, output: &mut Output, t0: f64, t1: f64, timer: &Timer) {
    let mut rng = rand::thread_rng();
    let mut temperature = t0;

    loop {
        temperature =
            t0.powf(1.0 - timer.get_time() / TIME_LIMIT) * t1.powf(timer.get_time() / TIME_LIMIT);

        for i in 51..101 {
            for j in (i + 1)..102 {
                let current_score = compute_score(&input, &output).0;

                let mut new_path = vec![];
                for k in 0..(i + 1) {
                    new_path.push(output.path[k]);
                }
                for k in ((i + 1)..(j + 1)).rev() {
                    new_path.push(output.path[k]);
                }
                for k in (j + 1)..output.path.len() {
                    new_path.push(output.path[k]);
                }

                let new_output = Output {
                    r: output.r.clone(),
                    path: new_path,
                };
                let new_score = compute_score(&input, &new_output).0;

                if new_score > current_score
                    || rng.gen_bool((((new_score - current_score) as f64) / temperature).exp())
                {
                    *output = new_output;
                }
            }
        }

        if timer.get_time() >= TIME_LIMIT {
            break;
        }
    }
}

#[derive(Clone, Copy, Debug)]
struct Point {
    x: i32,
    y: i32,
}

impl Point {
    fn new(x: i32, y: i32) -> Point {
        Point { x, y }
    }

    fn distance(&self, other: &Point) -> i32 {
        return (self.x - other.x).abs() + (self.y - other.y).abs();
    }
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

#[derive(Clone)]
pub struct Output {
    r: Vec<usize>,
    path: Vec<(i32, i32)>,
}

impl Output {
    fn print(&self) {
        print!("50 ");
        for &r_i in self.r.iter() {
            print!("{} ", r_i + 1);
        }
        print!("\n{} ", self.path.len());
        for &(x, y) in self.path.iter() {
            print!("{} {} ", x, y);
        }
        println!("");
    }
}

const N: usize = 1000;
const M: usize = 50;

pub struct Input {
    from: Vec<(i32, i32)>,
    to: Vec<(i32, i32)>,
}

impl std::fmt::Display for Input {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        for i in 0..N {
            writeln!(
                f,
                "{} {} {} {}",
                self.from[i].0, self.from[i].1, self.to[i].0, self.to[i].1
            )?;
        }
        Ok(())
    }
}

pub fn get_input() -> Input {
    input! {
        a: [(i32, i32, i32, i32); N]
    }
    let from = a.iter().map(|&(x, y, _, _)| (x, y)).collect();
    let to = a.iter().map(|&(_, _, x, y)| (x, y)).collect();
    Input { from, to }
}

pub fn parse_output(_input: &Input, f: &str) -> Vec<Output> {
    let mut out = vec![];
    let mut f = proconio::source::once::OnceSource::from(f);
    while !f.is_empty() {
        input! {
            from &mut f,
            r: [usize],
            path: [(i32, i32)],
        }
        out.push(Output {
            r: r.into_iter().map(|i| i - 1).collect(),
            path,
        });
    }
    out
}

fn dist((x1, y1): (i32, i32), (x2, y2): (i32, i32)) -> i32 {
    (x1 - x2).abs() + (y1 - y2).abs()
}

pub fn compute_score(input: &Input, out: &Output) -> (i64, String, i64) {
    let mut time = 0;
    for i in 1..out.path.len() {
        time += dist(out.path[i - 1], out.path[i]) as i64;
    }
    for i in 0..out.r.len() {
        if out.r[i] >= N {
            return (
                0,
                format!("Illegal output (r[{}] = {})", i + 1, out.r[i] + 1),
                time,
            );
        }
        for j in 0..i {
            if out.r[i] == out.r[j] {
                return (
                    0,
                    format!("Illegal output (r[{}] = r[{}])", i + 1, j + 1),
                    time,
                );
            }
        }
    }
    for i in 0..out.path.len() {
        if out.path[i].0 < 0 || out.path[i].0 > 800 || out.path[i].1 < 0 || out.path[i].1 > 800 {
            return (0, "Illegal output".to_owned(), time);
        }
    }
    if out.path.len() == 0 || out.path[0] != (400, 400) {
        return (
            0,
            "Illegal output (x[1],y[1]) != (400, 400)".to_owned(),
            time,
        );
    } else if out.path[out.path.len() - 1] != (400, 400) {
        return (
            0,
            "Illegal output (x[n],y[n]) != (400, 400)".to_owned(),
            time,
        );
    }
    let mut first_visit = BTreeMap::new();
    let mut last_visit = BTreeMap::new();
    for i in 0..out.path.len() {
        first_visit.entry(out.path[i]).or_insert(i);
        last_visit.insert(out.path[i], i);
    }
    for &i in &out.r {
        if let (Some(first), Some(last)) = (
            first_visit.get(&input.from[i]),
            last_visit.get(&input.to[i]),
        ) {
            if first >= last {
                return (
                    0,
                    format!("{}-th delivery has not been completed", i + 1),
                    time,
                );
            }
        } else {
            return (
                0,
                format!("{}-th delivery has not been completed", i + 1),
                time,
            );
        }
    }
    if out.r.len() != M {
        return (0, "Illegal output (m != 50)".to_owned(), time);
    }
    let score = (1e8 / (1000 + time) as f64).round() as i64;
    (score, String::new(), time)
}
