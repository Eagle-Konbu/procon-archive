#![allow(non_snake_case, unused_macros)]
use rand::*;
use std::collections::{BinaryHeap, HashMap, HashSet};

use proconio::{input, marker::*};
// use rand::prelude::*;

const TIMELIMIT: f64 = 2.5;

const COUNT: usize = 100;
const MIN_K: usize = 2;
const MAX_K: usize = 5;
const MIN_N: [usize; 6] = [0, 0, 15, 18, 21, 24];
const MAX_N: [usize; 6] = [0, 0, 39, 42, 45, 48];

fn main() {
    let input = get_input();

    let mut sim = Sim::new(&input);
    let mut output = Output {
        moves: random_move(&mut sim, 50 * input.k),
        connects: vec![],
    };

    connect(&mut sim, &mut output);

    print_output(&output, true);

    eprintln!("{}", sim.compute_score().0);
}

fn random_move(sim: &mut Sim, move_cnt: usize) -> Vec<(usize, usize, usize, usize)> {
    let mut rng = rand::thread_rng();

    let mut moves = vec![];
    let mut computers = vec![];
    for x in 0..sim.n {
        for y in 0..sim.n {
            if sim.grid[x][y] != 0 {
                computers.push((x, y));
            }
        }
    }
    for _ in 0..move_cnt {
        let idx = rng.gen_range(0, computers.len());
        let (x, y) = computers[idx];
        let dir = rng.gen_range(0, 4);

        // let (nx, ny) = match dir {
        //     0 => (x, y - 1),
        //     1 => (x, y + 1),
        //     2 => (x - 1, y),
        //     3 => (x + 1, y),
        //     _ => unreachable!(),
        // };
        // if sim.grid[nx][ny] == 0 {
        //     moves.push((x, y, nx, ny));
        //     computers[idx] = (nx, ny);
        // }
        match dir {
            0 => {
                if y > 0 && sim.grid[x][y - 1] == 0 {
                    moves.push((x, y, x, y - 1));
                    sim.apply_move(x, y, x, y - 1);
                    computers[idx] = (x, y - 1);
                }
            }
            1 => {
                if y < sim.n - 1 && sim.grid[x][y + 1] == 0 {
                    moves.push((x, y, x, y + 1));
                    sim.apply_move(x, y, x, y + 1);
                    computers[idx] = (x, y + 1);
                }
            }
            2 => {
                if x > 0 && sim.grid[x - 1][y] == 0 {
                    moves.push((x, y, x - 1, y));
                    sim.apply_move(x, y, x - 1, y);
                    computers[idx] = (x - 1, y);
                }
            }
            3 => {
                if x < sim.n - 1 && sim.grid[x + 1][y] == 0 {
                    moves.push((x, y, x + 1, y));
                    sim.apply_move(x, y, x + 1, y);
                    computers[idx] = (x + 1, y);
                }
            }
            _ => unreachable!(),
        }
    }

    moves
}

fn connect(sim: &mut Sim, output: &mut Output) {
    let mut remaning_cnt = 100 * sim.k - sim.moves;
    for x in 0..sim.n {
        for y in 0..sim.n {
            if sim.grid[x][y] == 0 {
                continue;
            }

            for d in 1..sim.n {
                if remaning_cnt <= 0 {
                    return;
                }

                if x + d < sim.n {
                    if sim.grid[x][y] == sim.grid[x + d][y] {
                        if sim.apply_connect(x, y, x + d, y).is_ok() {
                            output.connects.push((x, y, x + d, y));
                            remaning_cnt -= 1;
                        }
                    }
                }

                if y + d < sim.n {
                    if sim.grid[x][y] == sim.grid[x][y + d] {
                        if sim.apply_connect(x, y, x, y + d).is_ok() {
                            output.connects.push((x, y, x, y + d));
                            remaning_cnt -= 1;
                        }
                    }
                }
            }
        }
    }
}

fn print_output(output: &Output, with_process: bool) {
    let turns_cnt = output.moves.len() + output.connects.len();

    if with_process {
        for turns in 1..=turns_cnt {
            let move_cnt = std::cmp::min(output.moves.len(), turns);
            println!("{}", move_cnt);
            for (i, (x1, y1, x2, y2)) in output.moves.iter().enumerate() {
                if i + 1 > move_cnt {
                    break;
                }
                println!("{} {} {} {}", x1, y1, x2, y2);
            }

            let connect_cnt = std::cmp::min(output.connects.len(), turns - move_cnt);
            println!("{}", connect_cnt);
            for (i, (x1, y1, x2, y2)) in output.connects.iter().enumerate() {
                if i + 1 > connect_cnt {
                    break;
                }

                println!("{} {} {} {}", x1, y1, x2, y2);
            }
        }
    } else {
        println!("{}", output.moves.len());
        for (x1, y1, x2, y2) in output.moves.iter() {
            println!("{} {} {} {}", x1, y1, x2, y2);
        }

        println!("{}", output.connects.len());
        for (x1, y1, x2, y2) in output.connects.iter() {
            println!("{} {} {} {}", x1, y1, x2, y2);
        }
    }
}

#[derive(Clone, Debug)]
pub struct UnionFind {
    par: Vec<usize>,
    size: Vec<usize>,
}

impl UnionFind {
    pub fn new(n: usize) -> Self {
        UnionFind {
            par: (0..n).into_iter().collect(),
            size: vec![1; n],
        }
    }

    pub fn find(&mut self, x: usize) -> usize {
        if self.par[x] == x {
            x
        } else {
            self.par[x] = self.find(self.par[x]);
            self.par[x]
        }
    }

    pub fn unite(&mut self, x: usize, y: usize) {
        let mut x = self.find(x);
        let mut y = self.find(y);
        if self.size[x] < self.size[y] {
            ::std::mem::swap(&mut x, &mut y);
        }
        if x != y {
            self.size[x] += self.size[y];
            self.par[y] = x;
        }
    }

    pub fn same(&mut self, x: usize, y: usize) -> bool {
        self.find(x) == self.find(y)
    }
}

#[derive(Clone, Debug)]
pub struct Input {
    pub n: usize,
    pub k: usize,
    pub grid: Vec<Vec<usize>>,
}

pub fn get_input() -> Input {
    input! {
        n: usize,
        k: usize,
        grid: [Chars; n]
    }
    let grid = grid
        .iter()
        .map(|row| {
            row.iter()
                .map(|&c| c.to_string().parse::<usize>().unwrap())
                .collect()
        })
        .collect();
    Input { n, k, grid }
}

#[derive(Clone, Debug)]
pub struct Output {
    pub moves: Vec<(usize, usize, usize, usize)>,
    pub connects: Vec<(usize, usize, usize, usize)>,
}

fn read<T: Copy + PartialOrd + std::fmt::Display + std::str::FromStr>(
    token: Option<&str>,
    lb: T,
    ub: T,
) -> Result<T, String> {
    if let Some(v) = token {
        if let Ok(v) = v.parse::<T>() {
            if v < lb || ub < v {
                Err(format!("Out of range: {}", v))
            } else {
                Ok(v)
            }
        } else {
            Err(format!("Parse error: {}", v))
        }
    } else {
        Err(format!("Unexpected EOF"))
    }
}

pub fn parse_multi_output(input: &Input, f: &str) -> Result<Vec<Output>, String> {
    let mut outputs = vec![];
    let mut tokens = f.split_whitespace();
    while let Some(num_moves) = tokens.next() {
        let mut moves = vec![];
        let mut connects = vec![];
        let num_moves = read(Some(num_moves), 0, 100 * input.k)?;
        for _ in 0..num_moves {
            let r0 = read(tokens.next(), 0, input.n - 1)?;
            let c0 = read(tokens.next(), 0, input.n - 1)?;
            let r1 = read(tokens.next(), 0, input.n - 1)?;
            let c1 = read(tokens.next(), 0, input.n - 1)?;
            moves.push((r0, c0, r1, c1));
        }

        let num_connects = read(tokens.next(), 0, 100 * input.k - num_moves)?;
        for _ in 0..num_connects {
            let r0 = read(tokens.next(), 0, input.n - 1)?;
            let c0 = read(tokens.next(), 0, input.n - 1)?;
            let r1 = read(tokens.next(), 0, input.n - 1)?;
            let c1 = read(tokens.next(), 0, input.n - 1)?;
            connects.push((r0, c0, r1, c1));
        }
        outputs.push(Output { moves, connects });
    }

    Ok(outputs)
}

pub fn parse_output(input: &Input, f: &str) -> Result<Output, String> {
    let mut output = parse_multi_output(input, f)?;
    if output.is_empty() {
        return Err(format!("no output"));
    }
    Ok(output.remove(0))
}

pub struct Outcome {
    pub n: usize,
    pub grid: Vec<Vec<usize>>,
    pub cables: Vec<(usize, usize, usize, usize)>,
    pub cid: Vec<Vec<usize>>,
}

pub struct Sim {
    n: usize,
    k: usize,
    grid: Vec<Vec<usize>>,
    cables: Vec<(usize, usize, usize, usize)>,
    cable_set: HashSet<(usize, usize, usize, usize)>,
    moves: usize,
    connects: usize,
}

impl Sim {
    pub fn new(input: &Input) -> Self {
        Sim {
            n: input.n,
            k: input.k,
            grid: input.grid.clone(),
            cables: Vec::new(),
            cable_set: HashSet::new(),
            moves: 0,
            connects: 0,
        }
    }

    fn check_inside(&self, r: usize, c: usize, marker: &str) -> Result<(), String> {
        if r >= self.n || c >= self.n {
            Err(format!("invalid coordinate: ({}, {}) ({})", r, c, marker))
        } else {
            Ok(())
        }
    }

    pub fn apply_move(&mut self, r0: usize, c0: usize, r1: usize, c1: usize) -> Result<(), String> {
        let marker = format!("move {}", self.moves);
        self.check_inside(r0, c0, &marker)?;
        self.check_inside(r1, c1, &marker)?;
        if abs_diff(r0, r1) + abs_diff(c0, c1) != 1 {
            return Err(format!(
                "illegal move: ({}, {}) -> ({}, {}) ({})",
                r0, c0, r1, c1, marker
            ));
        }
        if self.grid[r0][c0] == 0 {
            return Err(format!(
                "illegal move: ({}, {}) is empty ({})",
                r0, c0, marker
            ));
        }
        if self.grid[r1][c1] != 0 {
            return Err(format!(
                "illegal move: ({}, {}) is not empty ({})",
                r1, c1, marker
            ));
        }
        self.grid[r1][c1] = self.grid[r0][c0];
        self.grid[r0][c0] = 0;
        self.moves += 1;
        Ok(())
    }

    fn check_identical_cable(
        &mut self,
        r0: usize,
        c0: usize,
        r1: usize,
        c1: usize,
        marker: &str,
    ) -> Result<(), String> {
        if self.cable_set.contains(&(r0, c0, r1, c1)) || self.cable_set.contains(&(r1, c1, r0, c0))
        {
            Err(format!(
                "illegal connect: identical cable exists ({}, {}) - ({}, {}) ({})",
                r0, c0, r1, c1, marker
            ))
        } else {
            self.cable_set.insert((r0, c0, r1, c1));
            self.cable_set.insert((r1, c1, r0, c0));
            Ok(())
        }
    }

    pub fn apply_connect(
        &mut self,
        r0: usize,
        c0: usize,
        r1: usize,
        c1: usize,
    ) -> Result<(), String> {
        let marker = format!("connect {}", self.connects);
        self.check_inside(r0, c0, &marker)?;
        self.check_inside(r1, c1, &marker)?;
        self.check_identical_cable(r0, c0, r1, c1, &marker)?;
        if r0 == r1 && c0 == c1 {
            return Err(format!(
                "illegal connect: same coordinates ({}, {}) - ({}, {}) ({})",
                r0, c0, r1, c1, marker
            ));
        }
        if r0 != r1 && c0 != c1 {
            return Err(format!(
                "illegal connect: not axis-aligned ({}, {}) - ({}, {}) ({})",
                r0, c0, r1, c1, marker
            ));
        }
        if self.grid[r0][c0] == 0 || self.grid[r0][c0] == !0 {
            return Err(format!(
                "illegal connect: computer does not exist on ({}, {}) ({})",
                r0, c0, marker
            ));
        }
        if self.grid[r1][c1] == 0 || self.grid[r1][c1] == !0 {
            return Err(format!(
                "illegal connect: computer does not exist on ({}, {}) ({})",
                r1, c1, marker
            ));
        }

        let (cr0, cr1) = if r0 == r1 {
            (r0, r1)
        } else {
            (r0.min(r1) + 1, r0.max(r1) - 1)
        };
        let (cc0, cc1) = if c0 == c1 {
            (c0, c1)
        } else {
            (c0.min(c1) + 1, c0.max(c1) - 1)
        };

        for r in cr0..=cr1 {
            for c in cc0..=cc1 {
                if self.grid[r][c] == !0 {
                    return Err(format!(
                        "illegal connect: cables cross at ({}, {}) ({})",
                        r, c, marker
                    ));
                }
                if self.grid[r][c] != 0 {
                    return Err(format!(
                        "illegal connect: computer exists on ({}, {}) ({})",
                        r, c, marker
                    ));
                }
            }
        }

        for r in cr0..=cr1 {
            for c in cc0..=cc1 {
                self.grid[r][c] = !0;
            }
        }
        self.cables.push((r0, c0, r1, c1));
        self.connects += 1;
        Ok(())
    }

    pub fn compute_score(&self) -> (i32, String, Outcome) {
        let mut uf = UnionFind::new(self.n * self.n);
        self.cables
            .iter()
            .for_each(|(r0, c0, r1, c1)| uf.unite(r0 * self.n + c0, r1 * self.n + c1));

        let mut pos = Vec::new();
        for r in 0..self.n {
            for c in 0..self.n {
                if self.grid[r][c] != !0 && self.grid[r][c] != 0 {
                    pos.push((r, c));
                }
            }
        }

        let computers = pos.len();
        let mut score = 0;
        for i in 0..computers {
            let (ri, ci) = pos[i];
            for j in i + 1..computers {
                let (rj, cj) = pos[j];
                if uf.same(ri * self.n + ci, rj * self.n + cj) {
                    if self.grid[ri][ci] == self.grid[rj][cj] {
                        score += 1;
                    } else {
                        score -= 1;
                    }
                }
            }
        }

        let mut component_ids = HashMap::new();
        let mut cid = vec![vec![!0; self.n]; self.n];
        for &(r, c) in pos.iter() {
            let p = uf.find(r * self.n + c);
            let sz = component_ids.len();
            let id = component_ids.entry(p).or_insert(sz);
            cid[r][c] = *id;
        }

        for &(r0, c0, r1, c1) in self.cables.iter() {
            let id = cid[r0][c0];
            for r in r0.min(r1)..=r0.max(r1) {
                for c in c0.min(c1)..=c0.max(c1) {
                    cid[r][c] = id;
                }
            }
        }

        let outcome = Outcome {
            n: self.n,
            grid: self.grid.clone(),
            cables: self.cables.clone(),
            cid,
        };
        if self.moves + self.connects > 100 * self.k {
            return (0, format!("too many moves"), outcome);
        }
        (score, String::new(), outcome)
    }
}

pub fn compute_score(input: &Input, output: &Output) -> (i32, String, Outcome) {
    let mut sim = Sim::new(input);
    for &(r0, c0, r1, c1) in output.moves.iter() {
        if let Err(err) = sim.apply_move(r0, c0, r1, c1) {
            return (0, err, sim.compute_score().2);
        }
    }
    for &(r0, c0, r1, c1) in output.connects.iter() {
        if let Err(err) = sim.apply_connect(r0, c0, r1, c1) {
            return (0, err, sim.compute_score().2);
        }
    }
    sim.compute_score()
}

fn abs_diff(a: usize, b: usize) -> usize {
    if a > b {
        a - b
    } else {
        b - a
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
        self.start_time = 0.0;
    }
}
