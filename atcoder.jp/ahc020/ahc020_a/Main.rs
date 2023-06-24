use itertools::Itertools;
use proconio::{input, marker::Usize1};
use rand::prelude::*;
// use rand_chacha::ChaCha20Rng;
// use rand_distr::Normal;
use std::collections::HashSet;

fn main() {
    let input = Input::get();
    let mut output = Output::new(&input);

    set_edges_on_mst(&input, &mut output);

    for (i, &(u, v, w)) in input.edges.iter().enumerate() {
        if output.edges[i] {
            output.powers[u] = 1000;
            output.powers[v] = 1000;
        }
    }

    output.print();
}

fn set_edges_on_mst(input: &Input, output: &mut Output) {
    let mut edges = vec![];
    for (i, &e) in input.edges.iter().enumerate() {
        edges.push((e, i));
    }
    edges.sort_by_key(|&((_, _, w), _)| w);

    let mut dsu = Dsu::new(input.n);

    for &((u, v, _), i) in edges.iter() {
        if dsu.same(u, v) {
            continue;
        }

        dsu.merge(u, v);
        output.edges[i] = true;
    }
}

pub const MAP_SIZE: i32 = 10000;
pub const MAP_SIZE2: i32 = MAP_SIZE * 2;
pub const MAX_POWER: i32 = 5000;
pub const MIN_BASE_COUNT: i32 = 100;
pub const MAX_BASE_COUNT: i32 = 100;
pub const MIN_BASE_DIST: i32 = 1000;
pub const MIN_HOUSE_COUNT: i32 = 2000;
pub const MAX_HOUSE_COUNT: i32 = 5000;
pub const MIN_PIVOT_COUNT: i32 = 20;
pub const MAX_PIVOT_COUNT: i32 = 40;
pub const MIN_PIVOT_DIST: i32 = 2000;
pub const PIVOT_MAP_SIZE: i32 = 8000;
pub const MIN_STD_DEV: f64 = 200.0;
pub const MAX_STD_DEV: f64 = 1000.0;
pub const MIN_EDGE_COST_COEF: f64 = 10.0;
pub const MAX_EDGE_COST_COEF: f64 = 50.0;

#[derive(Clone, Debug)]
pub struct Input {
    pub n: usize,
    pub m: usize,
    pub k: usize,
    pub stations: Vec<Point>,
    pub edges: Vec<(usize, usize, i32)>,
    pub residents: Vec<Point>,
}

impl Input {
    fn get() -> Input {
        input! {
            n: usize,
            m: usize,
            k: usize,
            stations: [(i32, i32); n],
            edges: [(Usize1, Usize1, i32); m],
            residents: [(i32, i32); k],
        }

        Input {
            n,
            m,
            k,
            stations: stations.iter().map(|&(x, y)| Point::new(x, y)).collect(),
            edges,
            residents: residents.iter().map(|&(x, y)| Point::new(x, y)).collect(),
        }
    }
}

#[derive(Clone, Debug, Eq, PartialEq)]
pub struct Output {
    pub powers: Vec<i32>,
    pub edges: Vec<bool>,
}

impl Output {
    fn new(input: &Input) -> Output {
        let powers = vec![0; input.n];
        let edges = vec![false; input.m];

        Output { powers, edges }
    }

    fn print(&self) {
        for &p in &self.powers {
            print!("{} ", p);
        }
        println!();

        for &b in &self.edges {
            print!("{} ", if b { 1 } else { 0 });
        }
        println!();
    }

    fn get_broadcasted_count(&self, input: &Input) -> usize {
        let is_connected = self.get_connection_status(input);
        self.get_broadcasted_status(input, &is_connected)
            .iter()
            .filter(|&&b| b)
            .count()
    }

    fn get_connection_status(&self, input: &Input) -> Vec<bool> {
        let mut dsu = Dsu::new(input.n);

        for (j, used) in self.edges.iter().enumerate() {
            if !used {
                continue;
            }

            let (u, v, _) = input.edges[j];
            dsu.merge(u, v);
        }

        (0..input.n).map(|i| dsu.same(0, i)).collect()
    }

    fn get_broadcasted_status(&self, input: &Input, is_connected: &[bool]) -> Vec<bool> {
        let mut broadcasted = vec![false; input.k];

        for i in 0..input.n {
            if !is_connected[i] {
                continue;
            }

            for k in 0..input.k {
                let dist_sq = input.stations[i].calc_sq_dist(&input.residents[k]);
                let power = self.powers[i];
                broadcasted[k] |= dist_sq <= power * power;
            }
        }

        broadcasted
    }

    fn calc_cost(&self, input: &Input) -> i64 {
        let mut cost = 0;

        for i in 0..input.n {
            cost += self.calc_power_cost(i);
        }

        for (j, used) in self.edges.iter().enumerate() {
            if !used {
                continue;
            }

            let (_, _, w) = input.edges[j];
            cost += w as i64;
        }

        cost
    }

    fn calc_power_cost(&self, v: usize) -> i64 {
        let p = self.powers[v] as i64;
        p * p
    }
}

#[derive(Clone, Debug, Copy, PartialEq, Eq, Hash)]
pub struct Point {
    pub x: i32,
    pub y: i32,
}

impl Point {
    pub const fn new(x: i32, y: i32) -> Self {
        Self { x, y }
    }

    pub fn calc_sq_dist(&self, other: &Point) -> i32 {
        let dx = self.x - other.x;
        let dy = self.y - other.y;
        dx * dx + dy * dy
    }
}

impl std::fmt::Display for Input {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        writeln!(f, "{} {} {}", self.n, self.m, self.k)?;
        for p in &self.stations {
            writeln!(f, "{} {}", p.x, p.y)?;
        }

        for &(u, v, w) in &self.edges {
            writeln!(f, "{} {} {}", u + 1, v + 1, w)?;
        }

        for p in &self.residents {
            writeln!(f, "{} {}", p.x, p.y)?;
        }

        Ok(())
    }
}

pub fn compute_score(input: &Input, out: &Output) -> (i64, String) {
    let broadcasted_count = out.get_broadcasted_count(&input);

    let score = if broadcasted_count < input.k {
        (1e6 * (broadcasted_count + 1) as f64 / input.k as f64).round() as i64
    } else {
        let cost = out.calc_cost(input);
        (1e6 * (1.0 + 1e8 / (cost as f64 + 1e7))).round() as i64
    };

    (score, String::new())
}

pub fn check_reachable(stations: &[Point], residents: &[Point]) -> bool {
    let mut remaining = residents.iter().collect_vec();

    for &station in stations {
        remaining.retain(|p| p.calc_sq_dist(&station) > MAX_POWER * MAX_POWER);
    }

    remaining.len() == 0
}

pub struct Dsu {
    n: usize,
    parent_or_size: Vec<i32>,
}

impl Dsu {
    pub fn new(size: usize) -> Self {
        Self {
            n: size,
            parent_or_size: vec![-1; size],
        }
    }

    pub fn merge(&mut self, a: usize, b: usize) -> usize {
        assert!(a < self.n);
        assert!(b < self.n);
        let (mut x, mut y) = (self.leader(a), self.leader(b));
        if x == y {
            return x;
        }
        if -self.parent_or_size[x] < -self.parent_or_size[y] {
            std::mem::swap(&mut x, &mut y);
        }
        self.parent_or_size[x] += self.parent_or_size[y];
        self.parent_or_size[y] = x as i32;
        x
    }

    pub fn same(&mut self, a: usize, b: usize) -> bool {
        assert!(a < self.n);
        assert!(b < self.n);
        self.leader(a) == self.leader(b)
    }

    pub fn leader(&mut self, a: usize) -> usize {
        assert!(a < self.n);
        if self.parent_or_size[a] < 0 {
            return a;
        }
        self.parent_or_size[a] = self.leader(self.parent_or_size[a] as usize) as i32;
        self.parent_or_size[a] as usize
    }

    pub fn size(&mut self, a: usize) -> usize {
        assert!(a < self.n);
        let x = self.leader(a);
        -self.parent_or_size[x] as usize
    }

    pub fn groups(&mut self) -> Vec<Vec<usize>> {
        let mut leader_buf = vec![0; self.n];
        let mut group_size = vec![0; self.n];
        for i in 0..self.n {
            leader_buf[i] = self.leader(i);
            group_size[leader_buf[i]] += 1;
        }
        let mut result = vec![Vec::new(); self.n];
        for i in 0..self.n {
            result[i].reserve(group_size[i]);
        }
        for i in 0..self.n {
            result[leader_buf[i]].push(i);
        }
        result
            .into_iter()
            .filter(|x| !x.is_empty())
            .collect::<Vec<Vec<usize>>>()
    }
}
