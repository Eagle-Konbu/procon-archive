use proconio::input;
use rand::prelude::*;

fn main() {
    let input = get_input();

    let mut handed_out_cnt = 0;
    let mut cut_lines = vec![];

    let mut base = 10;
    let mut base_cnt = 0;

    for y in -10000..=10000 {
        let strawberry_cnt =
            (input.xy.iter().filter(|&point| point.1 <= y).count() as i32) - handed_out_cnt;
        if strawberry_cnt >= base {
            cut_lines.push((-10000, y, 10000, y));
            handed_out_cnt += base;
            base_cnt += 1;
            if input.a[(base - 1) as usize] == base_cnt {
                base -= 1;
            }
        }
        if base == 0 {
            break;
        }
        if cut_lines.len() >= input.k {
            break;
        }
    }

    println!("{}", cut_lines.len());
    for (x1, y1, x2, y2) in cut_lines {
        println!("{} {} {} {}", x1, y1, x2, y2);
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

pub type Output = Vec<(i32, i32, i32, i32)>;

#[derive(Clone, Debug)]
pub struct Input {
    pub n: usize,
    pub k: usize,
    pub xy: Vec<(i32, i32)>,
    pub a: Vec<i32>,
}

impl std::fmt::Display for Input {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        writeln!(f, "{} {}", self.n, self.k)?;
        for d in 0..10 {
            if d > 0 {
                write!(f, " ")?;
            }
            write!(f, "{}", self.a[d])?;
        }
        writeln!(f)?;
        for i in 0..self.n {
            writeln!(f, "{} {}", self.xy[i].0, self.xy[i].1)?;
        }
        Ok(())
    }
}

pub fn get_input() -> Input {
    input! {
        n: usize, k: usize,
        a: [i32; 10],
        xy: [(i32, i32); n],
    }
    Input { n, k, xy, a }
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
        Err("Unexpected EOF".to_owned())
    }
}

pub fn parse_output(input: &Input, f: &str) -> Result<Vec<Output>, String> {
    let mut out = vec![];
    let mut tokens = f.split_whitespace();
    while let Some(k) = tokens.next() {
        let k = read::<usize>(Some(k), 0, input.k)?;
        let mut pq = vec![];
        for _ in 0..k {
            let px = read(tokens.next(), -1000000000, 1000000000)?;
            let py = read(tokens.next(), -1000000000, 1000000000)?;
            let qx = read(tokens.next(), -1000000000, 1000000000)?;
            let qy = read(tokens.next(), -1000000000, 1000000000)?;
            if (px, py) == (qx, qy) {
                return Err(format!("(px, py) must be different from (qx, qy)"));
            }
            pq.push((px, py, qx, qy));
        }
        out.push(pq);
    }
    Ok(out)
}

pub fn compute_score(input: &Input, out: &Output) -> (i64, String, (Vec<i32>, Vec<Vec<usize>>)) {
    let mut pieces = vec![(0..input.n).collect::<Vec<_>>()];
    for &(px, py, qx, qy) in out {
        let mut new_pieces = vec![];
        for piece in pieces {
            let mut left = vec![];
            let mut right = vec![];
            for j in piece {
                let (x, y) = input.xy[j];
                let side = (qx - px) as i64 * (y - py) as i64 - (qy - py) as i64 * (x - px) as i64;
                if side > 0 {
                    left.push(j);
                } else if side < 0 {
                    right.push(j);
                }
            }
            if left.len() > 0 {
                new_pieces.push(left);
            }
            if right.len() > 0 {
                new_pieces.push(right);
            }
        }
        pieces = new_pieces;
    }
    let mut b = vec![0; 10];
    for piece in &pieces {
        if piece.len() <= 10 {
            b[piece.len() - 1] += 1;
        }
    }
    let mut num = 0;
    let mut den = 0;
    for d in 0..10 {
        num += input.a[d].min(b[d]);
        den += input.a[d];
    }
    let score = (1e6 * num as f64 / den as f64).round() as i64;
    (score, String::new(), (b, pieces))
}
