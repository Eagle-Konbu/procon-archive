#![allow(non_snake_case, unused_macros)]
use std::io::{self, BufReader};

use itertools::Itertools;
use proconio::{input, source::line::LineSource};
use rand::prelude::*;

const MONTE_CARLO_COUNT: usize = 100;

fn main() {
    let mut stdin = LineSource::new(BufReader::new(io::stdin()));
    macro_rules! input(($($tt:tt)*) => (proconio::input!(from &mut stdin, $($tt)*)));

    let mut rng = thread_rng();

    input! {
        fs: [usize; N*N]
    };
    let mut input = Input { fs, ps: vec![] };

    let mut prev_state: Option<State> = None;

    for t in 0..100 {
        input! {
            p: usize,
        }
        input.ps.push(p);

        let moves = vec!['F', 'B', 'L', 'R'];
        let mut new_states = moves
            .iter()
            .map(|&c| {
                let mut new_state = State::new(&input);
                if prev_state.is_some() {
                    new_state = prev_state.clone().unwrap();
                    new_state.ps.push(p);
                }
                new_state.apply_move(c);
                new_state
            })
            .collect::<Vec<_>>();

        let mut max_idx = !0;
        let mut score = -1;
        for i in 0..4 {
            // let new_score = random(&input, &mut new_states[i].clone(), &mut rng);
            let mut new_score = 0;
            for _ in 0..MONTE_CARLO_COUNT {
                new_score += random(&input, &mut new_states[i].clone(), &mut rng, 0);
            }
            eprintln!("{} {}: {}", t, moves[i], new_score as f64 / MONTE_CARLO_COUNT as f64);
            if new_score > score {
                score = new_score;
                max_idx = i;
                prev_state = Some(new_states[i].clone());
            }
        }

        println!("{}", moves[max_idx]);
    }
}

fn random(input: &Input, state: &mut State, rng: &mut ThreadRng, cnt: usize) -> i64 {
    let moves = vec!['L', 'R', 'F', 'B'];
    let move_to_apply = moves[rng.gen_range(0, moves.len())];

    state.ps.push(rng.gen_range(1, 101 - state.t + 1));
    state.apply_move(move_to_apply);

    if cnt >= 10 || state.t >= 100 {
        compute_score(input, state)
    } else {
        random(input, state, rng, cnt+1)
    }
}

#[macro_export]
macro_rules! mat {
	($($e:expr),*) => { Vec::from(vec![$($e),*]) };
	($($e:expr,)*) => { Vec::from(vec![$($e),*]) };
	($e:expr; $d:expr) => { Vec::from(vec![$e; $d]) };
	($e:expr; $d:expr $(; $ds:expr)+) => { Vec::from(vec![mat![$e $(; $ds)*]; $d]) };
}

pub const N: usize = 10;
pub const M: usize = 3;

pub type Output = Vec<char>;

#[derive(Clone, Debug)]
pub struct Input {
    pub fs: Vec<usize>,
    pub ps: Vec<usize>,
}

#[derive(Clone, Debug)]
pub struct State {
    pub fs: Vec<usize>,
    pub ps: Vec<usize>,
    pub board: Vec<Vec<usize>>,
    pub t: usize,
    pub last: (usize, usize),
}

impl State {
    pub fn new(input: &Input) -> Self {
        let mut board = mat![0; N; N];
        let last = ((input.ps[0] - 1) / N, (input.ps[0] - 1) % N);
        board[last.0][last.1] = input.fs[0];
        Self {
            fs: input.fs.clone(),
            ps: input.ps.clone(),
            board,
            t: 0,
            last,
        }
    }
    pub fn apply_move(&mut self, dir: char) -> Result<(), String> {
        match dir {
            'L' => {
                for i in 0..N {
                    let mut k = 0;
                    for j in 0..N {
                        if self.board[i][j] != 0 {
                            self.board[i][k] = self.board[i][j];
                            if k != j {
                                self.board[i][j] = 0;
                            }
                            k += 1;
                        }
                    }
                }
            }
            'R' => {
                for i in 0..N {
                    let mut k = N - 1;
                    for j in (0..N).rev() {
                        if self.board[i][j] != 0 {
                            self.board[i][k] = self.board[i][j];
                            if k != j {
                                self.board[i][j] = 0;
                            }
                            k -= 1;
                        }
                    }
                }
            }
            'F' => {
                for j in 0..N {
                    let mut k = 0;
                    for i in 0..N {
                        if self.board[i][j] != 0 {
                            self.board[k][j] = self.board[i][j];
                            if k != i {
                                self.board[i][j] = 0;
                            }
                            k += 1;
                        }
                    }
                }
            }
            'B' => {
                for j in 0..N {
                    let mut k = N - 1;
                    for i in (0..N).rev() {
                        if self.board[i][j] != 0 {
                            self.board[k][j] = self.board[i][j];
                            if k != i {
                                self.board[i][j] = 0;
                            }
                            k -= 1;
                        }
                    }
                }
            }
            _ => {
                return Err(format!("Illegal output: {}", dir));
            }
        }
        let mut p = 0;
        for i in 0..N {
            for j in 0..N {
                if self.board[i][j] == 0 {
                    p += 1;
                    if p == self.ps[self.t] {
                        self.board[i][j] = self.fs[self.t];
                        self.last = (i, j);
                    }
                }
            }
        }
        self.t += 1;
        Ok(())
    }
}

pub const DIJ: [(usize, usize); 4] = [(1, 0), (0, 1), (!0, 0), (0, !0)];

pub fn compute_score(input: &Input, state: &State) -> i64 {
    let mut visited = mat![false; N; N];
    let mut num = 0;
    for i in 0..N {
        for j in 0..N {
            if !visited[i][j] && state.board[i][j] != 0 {
                visited[i][j] = true;
                let c = state.board[i][j];
                let mut size = 1;
                let mut stack = vec![(i, j)];
                while let Some((i, j)) = stack.pop() {
                    for &(di, dj) in &DIJ {
                        let i2 = i + di;
                        let j2 = j + dj;
                        if i2 < N && j2 < N && !visited[i2][j2] && state.board[i2][j2] == c {
                            visited[i2][j2] = true;
                            stack.push((i2, j2));
                            size += 1;
                        }
                    }
                }
                num += size * size;
            }
        }
    }
    let mut d = vec![0; M + 1];
    for &f in &input.fs {
        d[f] += 1;
    }
    (1e6 * num as f64 / d[1..].iter().map(|d| d * d).sum::<i32>() as f64).round() as i64
}
