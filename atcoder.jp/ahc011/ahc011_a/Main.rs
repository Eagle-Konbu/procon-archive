#![allow(non_snake_case, unused_macros)]
use proconio::{input, marker::*};
use rand::{prelude::ThreadRng, Rng};

const TIMELIMIT: f64 = 2.8;

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
    let mut rng = rand::thread_rng();
    let args: Vec<String> = std::env::args().collect();

    let input = get_input();
    let n = input.n;

    let mut tiles = input.tiles.clone();

    let mut output: Output = vec![];

    let blank_pos = find_blank_pos(&tiles);

    let loop6 = 7;
    let loop7 = 10;
    let loop8 = 17;
    let loop9 = 33;
    let loop10 = 41;
    let chokudai_width = 35;

    // let loop6 = args[1].parse::<usize>().unwrap();
    // let loop7 = args[2].parse::<usize>().unwrap();
    // let loop8 = args[3].parse::<usize>().unwrap();
    // let loop9 = args[4].parse::<usize>().unwrap();
    // let loop10 = args[5].parse::<usize>().unwrap();
    // let chokudai_width = args[1].parse::<usize>().unwrap();

    let mut heap_list = vec![BinaryHeap::new(); input.T + 1];
    let max_depth = input.T;
    heap_list[0].push((
        compute_score(&input, &output).0,
        blank_pos,
        blank_pos,
        output.clone(),
    ));

    let mut max_score = -1;

    loop {
        if timer.get_time() >= TIMELIMIT {
            break;
        }

        for t in 0..max_depth {
            if timer.get_time() >= TIMELIMIT {
                break;
            }

            for i in 0..chokudai_width {
                if heap_list[t].is_empty() {
                    break;
                }

                let item = heap_list[t].pop().unwrap();
                let point = item.1;
                let previous_point = item.2;
                let current_output = item.3;

                for j in 0..4 {
                    let adj_point = (point.0 + DIJ[j].0, point.1 + DIJ[j].1);
                    if out_of_range(n as i32, adj_point) || adj_point == previous_point {
                        continue;
                    }

                    let mut new_output = current_output.clone();
                    new_output.push(DIR[j]);

                    // 無駄なやつ検出
                    let mut is_cycle = false;
                    let mut pos_tmp = (0, 0);
                    let cycle_size_list = vec![loop6, loop7, loop8, loop9, loop10];
                    let cycle_size = cycle_size_list[input.n - 6];

                    let score = compute_score(&input, &new_output).0;

                    for k in 0..cycle_size {
                        if new_output.len() - 1 - k < cycle_size {
                            break;
                        }

                        let action = new_output[new_output.len() - 1 - k];
                        let idx = DIR.iter().position(|&x| x == action).unwrap();
                        pos_tmp.0 -= DIJ[idx].0;
                        pos_tmp.1 -= DIJ[idx].1;

                        if pos_tmp == (0, 0) {
                            is_cycle = true;
                        }
                    }

                    if score > max_score {
                        max_score = score;
                        output = new_output.clone();
                    }

                    if !is_cycle {
                        heap_list[t + 1].push((score, adj_point, point, new_output));
                    }
                }
            }
        }
    }

    for i in 0..std::cmp::min(output.len(), input.T) {
        print!("{}", output[i]);
    }
    println!("");

    // println!("{}", max_score);
}

fn out_of_range(n: i32, pos: (i32, i32)) -> bool {
    if pos.0 < 0 || pos.0 >= n || pos.1 < 0 || pos.1 >= n {
        return true;
    } else {
        return false;
    }
}

fn swap_tiles(blank_pos: (usize, usize), target: (usize, usize), tiles: &mut Vec<Vec<usize>>) {
    let tmp = tiles[target.0][target.1];
    tiles[target.0][target.1] = 0;
    tiles[blank_pos.0][blank_pos.1] = tmp;
}

fn swap_and_score(dir_idx: usize, input: &Input, output: &mut Output) -> i64 {
    output.push(DIR[dir_idx]);
    let score = compute_score(input, output).0;
    output.pop();
    return score;
}

fn find_blank_pos(tiles: &Vec<Vec<usize>>) -> (i32, i32) {
    let n = tiles.len();
    for i in 0..n {
        for j in 0..n {
            if tiles[i][j] == 0 {
                return (i as i32, j as i32);
            }
        }
    }

    return (0, 0);
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

use std::{
    cell::Cell,
    collections::{BinaryHeap, VecDeque},
};

#[derive(Clone, Debug)]
pub struct UnionFind {
    /// size / parent
    ps: Vec<Cell<usize>>,
    pub is_root: Vec<bool>,
}

impl UnionFind {
    pub fn new(n: usize) -> UnionFind {
        UnionFind {
            ps: vec![Cell::new(1); n],
            is_root: vec![true; n],
        }
    }
    pub fn find(&self, x: usize) -> usize {
        if self.is_root[x] {
            x
        } else {
            let p = self.find(self.ps[x].get());
            self.ps[x].set(p);
            p
        }
    }
    pub fn unite(&mut self, x: usize, y: usize) {
        let mut x = self.find(x);
        let mut y = self.find(y);
        if x == y {
            return;
        }
        if self.ps[x].get() < self.ps[y].get() {
            ::std::mem::swap(&mut x, &mut y);
        }
        *self.ps[x].get_mut() += self.ps[y].get();
        self.ps[y].set(x);
        self.is_root[y] = false;
    }
    pub fn same(&self, x: usize, y: usize) -> bool {
        self.find(x) == self.find(y)
    }
    pub fn size(&self, x: usize) -> usize {
        self.ps[self.find(x)].get()
    }
}

pub type Output = Vec<char>;

pub const DIJ: [(i32, i32); 4] = [(0, -1), (-1, 0), (0, 1), (1, 0)];
pub const DIR: [char; 4] = ['L', 'U', 'R', 'D'];

#[derive(Clone, Debug)]
pub struct Input {
    pub n: usize,
    pub T: usize,
    pub tiles: Vec<Vec<usize>>,
}

impl std::fmt::Display for Input {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        writeln!(f, "{} {}", self.n, self.T)?;
        for i in 0..self.n {
            for j in 0..self.n {
                write!(f, "{:0x}", self.tiles[i][j])?;
            }
            writeln!(f)?;
        }
        Ok(())
    }
}

pub fn get_input() -> Input {
    input! {
        n: usize,
        T: usize,
        tiles: [Chars; n]
    }
    let tiles = tiles
        .iter()
        .map(|ts| {
            ts.iter()
                .map(|&c| usize::from_str_radix(&c.to_string(), 16).unwrap())
                .collect()
        })
        .collect();
    Input { n, T, tiles }
}

pub fn parse_output(_input: &Input, f: &str) -> Result<Output, String> {
    Ok(f.trim().chars().collect())
}

pub struct Sim {
    n: usize,
    T: usize,
    from: Vec<Vec<(usize, usize)>>,
    turn: usize,
    i: usize,
    j: usize,
}

impl Sim {
    pub fn new(input: &Input) -> Self {
        let mut i = !0;
        let mut j = !0;
        let mut from = mat![(0, 0); input.n; input.n];
        for x in 0..input.n {
            for y in 0..input.n {
                if input.tiles[x][y] == 0 {
                    i = x;
                    j = y;
                }
                from[x][y] = (x, y);
            }
        }
        Sim {
            n: input.n,
            T: input.T,
            from,
            turn: 0,
            i,
            j,
        }
    }
    pub fn apply(&mut self, c: char) -> Result<(), String> {
        if let Some(d) = DIR.iter().position(|&d| d == c) {
            let i2 = (self.i as i32 + DIJ[d].0) as usize;
            let j2 = (self.j as i32 + DIJ[d].1) as usize;
            if i2 >= self.n || j2 >= self.n {
                Err(format!("illegal move: {} (turn {})", c, self.turn))
            } else {
                let f1 = self.from[self.i][self.j];
                let f2 = self.from[i2][j2];
                self.from[i2][j2] = f1;
                self.from[self.i][self.j] = f2;
                self.i = i2;
                self.j = j2;
                self.turn += 1;
                Ok(())
            }
        } else {
            Err(format!("illegal move: {} (turn {})", c, self.turn))
        }
    }
    pub fn compute_score(&self, input: &Input) -> (i64, String, Vec<Vec<bool>>) {
        let mut uf = UnionFind::new(self.n * self.n);
        let mut tree = vec![true; self.n * self.n];
        let mut tiles = mat![0; self.n; self.n];
        for i in 0..self.n {
            for j in 0..self.n {
                tiles[i][j] = input.tiles[self.from[i][j].0][self.from[i][j].1];
            }
        }
        for i in 0..self.n {
            for j in 0..self.n {
                if i + 1 < self.n && tiles[i][j] & 8 != 0 && tiles[i + 1][j] & 2 != 0 {
                    let a = uf.find(i * self.n + j);
                    let b = uf.find((i + 1) * self.n + j);
                    if a == b {
                        tree[a] = false;
                    } else {
                        let t = tree[a] && tree[b];
                        uf.unite(a, b);
                        tree[uf.find(a)] = t;
                    }
                }
                if j + 1 < self.n && tiles[i][j] & 4 != 0 && tiles[i][j + 1] & 1 != 0 {
                    let a = uf.find(i * self.n + j);
                    let b = uf.find(i * self.n + j + 1);
                    if a == b {
                        tree[a] = false;
                    } else {
                        let t = tree[a] && tree[b];
                        uf.unite(a, b);
                        tree[uf.find(a)] = t;
                    }
                }
            }
        }
        let mut max_tree = !0;
        for i in 0..self.n {
            for j in 0..self.n {
                if tiles[i][j] != 0 && tree[uf.find(i * self.n + j)] {
                    if max_tree == !0 || uf.size(max_tree) < uf.size(i * self.n + j) {
                        max_tree = i * self.n + j;
                    }
                }
            }
        }
        let mut bs = mat![false; self.n; self.n];
        if max_tree != !0 {
            for i in 0..self.n {
                for j in 0..self.n {
                    bs[i][j] = uf.same(max_tree, i * self.n + j);
                }
            }
        }
        if self.turn > self.T {
            return (0, format!("too many moves"), bs);
        }
        let size = if max_tree == !0 { 0 } else { uf.size(max_tree) };
        let score = if size == self.n * self.n - 1 {
            (500000.0 * (1.0 + (self.T - self.turn) as f64 / self.T as f64)).round()
        } else {
            (500000.0 * size as f64 / (self.n * self.n - 1) as f64).round()
        } as i64;
        (score, String::new(), bs)
    }
}

pub fn compute_score(
    input: &Input,
    out: &Output,
) -> (i64, String, (Vec<Vec<(usize, usize)>>, Vec<Vec<bool>>)) {
    let mut sim = Sim::new(input);
    for &c in out.iter() {
        if let Err(err) = sim.apply(c) {
            return (0, err, (sim.from.clone(), sim.compute_score(input).2));
        }
    }
    let (score, err, tree) = sim.compute_score(input);
    (score, err, (sim.from.clone(), tree))
}
