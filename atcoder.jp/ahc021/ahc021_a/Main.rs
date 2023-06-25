use itertools::Itertools;
use proconio::input;

fn main() {
    let input = Input::get();

    let out1 = solve1(&input);
    let out2 = solve2(&input);

    if compute_score(&input, &out1) < compute_score(&input, &out2) {
        print_output(&out2);
    } else {
        print_output(&out1);
    }
}

fn solve1(input: &Input) -> Output {
    let mut out = vec![];

    let mut state = input.clone();

    let mut target_pos = (0, 0);

    for i in 0..465 {
        let mut pos = (0, 0);
        for x in 0..N {
            for y in 0..=x {
                if state.bs[x][y] == i {
                    pos = (x, y);
                }
            }
        }

        if pos.0 == target_pos.0 {
            continue;
        }

        loop {
            if pos.1 == target_pos.1 {
                break;
            }

            if out.len() >= MAX_K {
                break;
            }

            let mut next_pos = pos;
            let (left, right) = (
                (pos.0 as i32, pos.1 as i32 - 1),
                (pos.0 as i32, pos.1 as i32 + 1),
            );

            if target_pos.1 < pos.1 {
                if target_pos.0 > pos.0 {
                    next_pos = (left.0 as usize, left.1 as usize);
                } else {
                    break;
                }
            } else {
                if target_pos.0 < pos.0 {
                    next_pos = (right.0 as usize, right.1 as usize);
                } else {
                    break;
                }
            }

            out.push((pos, next_pos));
            let tmp = state.bs[pos.0][pos.1];
            state.bs[pos.0][pos.1] = state.bs[next_pos.0][next_pos.1];
            state.bs[next_pos.0][next_pos.1] = tmp;

            pos = next_pos;
        }

        if target_pos.0 < pos.0 {
            loop {
                if pos.0 == target_pos.0 {
                    break;
                }

                if out.len() >= MAX_K {
                    break;
                }

                let mut next_pos = pos;
                let (upper_left, upper_right) = (
                    (pos.0 as i32 - 1, pos.1 as i32 - 1),
                    (pos.0 as i32 - 1, pos.1 as i32),
                );

                next_pos = (upper_right.0 as usize, upper_right.1 as usize);
                if pos.1 > target_pos.1 {
                    next_pos = (upper_left.0 as usize, upper_left.1 as usize);
                }

                out.push((pos, next_pos));
                let tmp = state.bs[pos.0][pos.1];
                state.bs[pos.0][pos.1] = state.bs[next_pos.0][next_pos.1];
                state.bs[next_pos.0][next_pos.1] = tmp;

                pos = next_pos;
            }

            loop {
                if pos.1 == target_pos.1 {
                    break;
                }

                if out.len() >= MAX_K {
                    break;
                }

                let mut next_pos = pos;
                let (left, right) = (
                    (pos.0 as i32, pos.1 as i32 - 1),
                    (pos.0 as i32, pos.1 as i32 + 1),
                );

                if target_pos.1 < pos.1 {
                    next_pos = (left.0 as usize, left.1 as usize);
                } else {
                    next_pos = (right.0 as usize, right.1 as usize);
                }

                out.push((pos, next_pos));
                let tmp = state.bs[pos.0][pos.1];
                state.bs[pos.0][pos.1] = state.bs[next_pos.0][next_pos.1];
                state.bs[next_pos.0][next_pos.1] = tmp;

                pos = next_pos;
            }
        } else {
            loop {
                if pos.0 == target_pos.0 {
                    break;
                }

                if out.len() >= MAX_K {
                    break;
                }

                let mut next_pos = pos;
                let (lower_left, lower_right) = (
                    (pos.0 as i32 + 1, pos.1 as i32),
                    (pos.0 as i32 + 1, pos.1 as i32 + 1),
                );

                next_pos = (lower_left.0 as usize, lower_left.1 as usize);

                if pos.1 < target_pos.1 {
                    next_pos = (lower_right.0 as usize, lower_right.1 as usize);
                }

                out.push((pos, next_pos));
                let tmp = state.bs[pos.0][pos.1];
                state.bs[pos.0][pos.1] = state.bs[next_pos.0][next_pos.1];
                state.bs[next_pos.0][next_pos.1] = tmp;

                pos = next_pos;
            }

            loop {
                if pos.1 == target_pos.1 {
                    break;
                }

                if out.len() >= MAX_K {
                    break;
                }

                let mut next_pos = pos;
                let (left, right) = (
                    (pos.0 as i32, pos.1 as i32 - 1),
                    (pos.0 as i32, pos.1 as i32 + 1),
                );

                if target_pos.1 < pos.1 {
                    next_pos = (left.0 as usize, left.1 as usize);
                } else {
                    next_pos = (right.0 as usize, right.1 as usize);
                }

                out.push((pos, next_pos));
                let tmp = state.bs[pos.0][pos.1];
                state.bs[pos.0][pos.1] = state.bs[next_pos.0][next_pos.1];
                state.bs[next_pos.0][next_pos.1] = tmp;

                pos = next_pos;
            }
        }
        target_pos.1 += 1;
        if target_pos.1 > target_pos.0 {
            target_pos.0 += 1;
            target_pos.1 = 0;
        }
    }

    eprintln!("out.len() = {}", out.len());
    for y in 0..N {
        let mut pos = (N - 1, y);
        loop {
            if out.len() >= MAX_K {
                break;
            }
            let mut next_pos = (pos.0 - 1, y);
            if next_pos.0 < next_pos.1 {
                next_pos.1 = next_pos.0;
            }

            if state.bs[next_pos.0][next_pos.1] < state.bs[pos.0][pos.1] {
                break;
            }

            out.push((pos, next_pos));
            let tmp = state.bs[pos.0][pos.1];
            state.bs[pos.0][pos.1] = state.bs[next_pos.0][next_pos.1];
            state.bs[next_pos.0][next_pos.1] = tmp;

            pos = next_pos;
        }
    }

    out
}

fn solve2(input: &Input) -> Output {
    let mut out = vec![];

    let mut state = input.clone();

    let mut target_pos = (0, 0);

    for i in 0..465 {
        let mut pos = (0, 0);
        for x in 0..N {
            for y in 0..=x {
                if state.bs[x][y] == i {
                    pos = (x, y);
                }
            }
        }

        if pos.0 == target_pos.0 {
            continue;
        }

        loop {
            if pos.1 == target_pos.1 {
                break;
            }

            if out.len() >= MAX_K {
                break;
            }

            let mut next_pos = pos;
            let (left, right) = (
                (pos.0 as i32, pos.1 as i32 - 1),
                (pos.0 as i32, pos.1 as i32 + 1),
            );

            if target_pos.1 < pos.1 {
                next_pos = (left.0 as usize, left.1 as usize);
            } else {
                next_pos = (right.0 as usize, right.1 as usize);
            }

            out.push((pos, next_pos));
            let tmp = state.bs[pos.0][pos.1];
            state.bs[pos.0][pos.1] = state.bs[next_pos.0][next_pos.1];
            state.bs[next_pos.0][next_pos.1] = tmp;

            pos = next_pos;
        }

        if target_pos.0 < pos.0 {
            loop {
                if pos.0 == target_pos.0 {
                    break;
                }

                if out.len() >= MAX_K {
                    break;
                }

                let mut next_pos = pos;
                let (upper_left, upper_right) = (
                    (pos.0 as i32 - 1, pos.1 as i32 - 1),
                    (pos.0 as i32 - 1, pos.1 as i32),
                );

                next_pos = (upper_right.0 as usize, upper_right.1 as usize);

                out.push((pos, next_pos));
                let tmp = state.bs[pos.0][pos.1];
                state.bs[pos.0][pos.1] = state.bs[next_pos.0][next_pos.1];
                state.bs[next_pos.0][next_pos.1] = tmp;

                pos = next_pos;
            }

            target_pos.1 += 1;
            if target_pos.1 > target_pos.0 {
                target_pos.0 += 1;
                target_pos.1 = 0;
            }
        } else {
            loop {
                if pos.0 == target_pos.0 {
                    break;
                }

                if out.len() >= MAX_K {
                    break;
                }

                let mut next_pos = pos;
                let (lower_left, lower_right) = (
                    (pos.0 as i32 + 1, pos.1 as i32),
                    (pos.0 as i32 + 1, pos.1 as i32 + 1),
                );

                if lower_left.1 >= 0 {
                    next_pos = (lower_left.0 as usize, lower_left.1 as usize);
                } else {
                    next_pos = (lower_right.0 as usize, lower_right.1 as usize);
                }

                out.push((pos, next_pos));
                let tmp = state.bs[pos.0][pos.1];
                state.bs[pos.0][pos.1] = state.bs[next_pos.0][next_pos.1];
                state.bs[next_pos.0][next_pos.1] = tmp;

                pos = next_pos;
            }

            target_pos.1 -= 1;
            if target_pos.1 == !0 {
                target_pos.0 += 1;
                target_pos.1 = target_pos.0;
            }
        }
    }

    for y in 0..N {
        let mut pos = (N - 1, y);
        loop {
            if out.len() >= MAX_K {
                break;
            }
            let mut next_pos = (pos.0 - 1, y);
            if next_pos.0 < next_pos.1 {
                next_pos.1 = next_pos.0;
            }

            eprintln!("{:?} {:?}", pos, next_pos);
            if state.bs[next_pos.0][next_pos.1] < state.bs[pos.0][pos.1] {
                break;
            }

            out.push((pos, next_pos));
            let tmp = state.bs[pos.0][pos.1];
            state.bs[pos.0][pos.1] = state.bs[next_pos.0][next_pos.1];
            state.bs[next_pos.0][next_pos.1] = tmp;

            pos = next_pos;
        }
    }

    out
}
#[macro_export]
macro_rules! mat {
	($($e:expr),*) => { Vec::from(vec![$($e),*]) };
	($($e:expr,)*) => { Vec::from(vec![$($e),*]) };
	($e:expr; $d:expr) => { Vec::from(vec![$e; $d]) };
	($e:expr; $d:expr $(; $ds:expr)+) => { Vec::from(vec![mat![$e $(; $ds)*]; $d]) };
}

const N: usize = 30;
const N2: usize = N * (N + 1) / 2;
const MAX_K: usize = 10000;

const MAX_Y: usize = 29;

pub type Output = Vec<((usize, usize), (usize, usize))>;

fn print_output(out: &Output) {
    println!("{}", out.len());
    for &((x1, y1), (x2, y2)) in out {
        println!("{} {} {} {}", x1, y1, x2, y2);
    }
}

#[derive(Clone, Debug)]
pub struct Input {
    pub bs: Vec<Vec<i32>>,
}

impl Input {
    fn get() -> Input {
        let mut bs = vec![];
        for i in 0..N {
            input! {
                b: [i32; i + 1]
            }
            bs.push(b);
        }
        Input { bs }
    }
}

impl std::fmt::Display for Input {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        for i in 0..self.bs.len() {
            writeln!(f, "{}", self.bs[i].iter().join(" "))?;
        }
        Ok(())
    }
}

pub fn compute_score(
    input: &Input,
    out: &[((usize, usize), (usize, usize))],
) -> (i64, String, Vec<Vec<i32>>) {
    let mut used = vec![vec![]; N];
    for i in 0..N {
        used[i] = vec![false; i + 1];
    }
    let mut bs = input.bs.clone();
    for (t, &(p, q)) in out.iter().enumerate() {
        if !is_adj(p, q) {
            return (
                0,
                format!(
                    "({}, {}) and ({}, {}) are not adjacent (turn {})",
                    p.0, p.1, q.0, q.1, t
                ),
                bs,
            );
        }
        let bp = bs[p.0][p.1];
        let bq = bs[q.0][q.1];
        bs[p.0][p.1] = bq;
        bs[q.0][q.1] = bp;
    }
    let mut num = 0;
    for x in 0..N - 1 {
        for y in 0..=x {
            if bs[x][y] > bs[x + 1][y] {
                num += 1;
            }
            if bs[x][y] > bs[x + 1][y + 1] {
                num += 1;
            }
        }
    }
    let score = if num == 0 {
        ((10000 - out.len()) * 5 + 50000) as i64
    } else {
        50000 - num * 50
    };
    (score, String::new(), bs)
}

fn is_adj((x1, y1): (usize, usize), (x2, y2): (usize, usize)) -> bool {
    if x1 == x2 {
        y1 == y2 + 1 || y1 + 1 == y2
    } else if x1 + 1 == x2 {
        y1 == y2 || y1 + 1 == y2
    } else if x1 == x2 + 1 {
        y1 == y2 || y1 == y2 + 1
    } else {
        false
    }
}

fn adj_list((x, y): (usize, usize)) -> Vec<(usize, usize)> {
    let mut res = vec![];
    if x >= 1 {
        res.push((x - 1, y));
        if y >= 1 {
            res.push((x - 1, y - 1));
        }
    }
    if y >= 1 {
        res.push((x, y - 1));
    }
    if x < MAX_Y {
        res.push((x + 1, y));
        if y < MAX_Y {
            res.push((x + 1, y + 1));
        }
    }
    if y < MAX_Y {
        res.push((x, y + 1));
    }
    res
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
