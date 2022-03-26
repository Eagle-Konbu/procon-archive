use std::{
    collections::VecDeque,
    io::{self, BufReader},
};

use proconio::{input, source::line::LineSource};

// use petgraph::{
//     algo::{bellman_ford, dijkstra},
//     graph::{NodeIndex, UnGraph},
// };

const TIMELIMIT: f64 = 1.8;

fn main() {
    let mut stdin = LineSource::new(BufReader::new(io::stdin()));
    macro_rules! input(($($tt:tt)*) => (proconio::input!(from &mut stdin, $($tt)*)));

    let mut timer = Timer::new();

    input! {
        house: (usize, usize),
        office: (usize, usize),
        p: f64,
    }

    // let mut g = UnGraph::<>::new();
    let mut edges = vec![vec![]; 20 * 20];

    for i in 0..20 {
        input! {
            h: String
        }
        for j in 0..h.len() {
            let c = h.chars().nth(j).unwrap();
            if c == '0' {
                edges[field_index(i, j)].push(field_index(i, j + 1));
                edges[field_index(i, j + 1)].push(field_index(i, j));
            }
        }
    }

    for i in 0..19 {
        input! {
            v: String
        }
        for j in 0..v.len() {
            let c = v.chars().nth(j).unwrap();
            if c == '0' {
                edges[field_index(i, j)].push(field_index(i + 1, j));
                edges[field_index(i + 1, j)].push(field_index(i, j));
            }
        }
    }

    let mut d = vec![-1; 20 * 20];
    let mut prev = vec![10000; 20 * 20];

    d[field_index(house.0, house.1)] = 0;
    let mut que = VecDeque::new();
    que.push_back(field_index(house.0, house.1));

    while !que.is_empty() {
        let v = que.pop_front().unwrap();
        for &vv in edges[v].iter() {
            if d[vv] == -1 {
                d[vv] = d[v] + 1;
                prev[vv] = v;
                que.push_back(vv);
            }
        }
    }

    let mut path = vec![];

    let mut idx = field_index(office.0, office.1);
    while prev[idx] != 10000 {
        path.push(idx);
        idx = prev[idx];
    }
    path.reverse();

    let mut ans = String::new();

    idx = field_index(house.0, house.1);
    for &v in path.iter() {
        let diff = v as i32 - idx as i32;
        idx = v;
        if diff == 1 {
            ans += "R";
        } else if diff == -1 {
            ans += "L";
        } else if diff == 20 {
            ans += "D";
        } else {
            ans += "U";
        }
    }

    println!("{}", &ans);
}

fn field_index(x: usize, y: usize) -> usize {
    return x * 20 + y;
}

fn field_position(idx: usize) -> (usize, usize) {
    let y = idx % 20;
    let x = (idx - y) / 20;

    return (x, y);
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
