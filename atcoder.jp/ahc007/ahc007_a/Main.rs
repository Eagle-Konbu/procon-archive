use std::io::{BufReader, self};

use itertools::Itertools;
use proconio::{input, source::line::LineSource};

use petgraph::unionfind::UnionFind;
use rand::{self, Rng};

fn main() {
    let mut stdin = LineSource::new(BufReader::new(io::stdin()));
    macro_rules! input(($($tt:tt)*) => (proconio::input!(from &mut stdin, $($tt)*)));

    let n = 400;
    let m = 1995;
    input! {
        xy: [(i32,i32); n],
        uv: [(usize,usize); m]
    };
    let points: Vec<Point> = xy.iter().map(|&(x, y)| Point { x, y }).collect();
    let edges: Vec<Edge> = uv.iter().map(|&(u, v)| Edge { u, v }).collect();

    let mut d_list = vec![];
    for i in 0..m {
        let e = &edges[i];
        let u = e.u;
        let v = e.v;

        let d = (((points[u].x - points[v].x).pow(2) + (points[u].y - points[v].y).pow(2)) as f64)
            .sqrt();
        let coefficient:f64 = rand::thread_rng().gen_range(1.0, 3.0);
        d_list.push((d * coefficient, i));
    }

    let s = 5000;
    let mut ans_candidates = vec![];
    for _ in 0..s {
        let mut d = vec![];
        for i in 0..m {
            let e = &edges[i];
            let u = e.u;
            let v = e.v;

            let d_tmp = (((points[u].x - points[v].x).pow(2) + (points[u].y - points[v].y).pow(2)) as f64)
                .sqrt();
            let coefficient:f64 = rand::thread_rng().gen_range(1.0, 3.0);
            d.push((d_tmp * coefficient, i));
        }
        ans_candidates.push(d);
    }


    let mut apply = vec![false; m];
    let mut uf = UnionFind::<usize>::new(n);

    let mut max_sum = 0.0;
    for _ in 0..s {
        let mut apply_tmp = vec![false; m];
        let mut sum_tmp = 0.0;
        //クラスカル法
        for &d in d_list.iter().sorted_by(|&a, &b| a.0.partial_cmp(&b.0).unwrap()) {
            let a = edges[d.1].u;
            let b = edges[d.1].v;

            if !uf.equiv(a, b) {
                uf.union(a, b);
                apply_tmp[d.1] = true;
                sum_tmp += d.0;
            }
        }
        if sum_tmp > max_sum {
            max_sum = sum_tmp;
            apply = apply_tmp;
        }
    }

    for i in 0..m {
        input! {
            l:i32
        }
        if apply[i] {
            println!("1");
        } else {
            println!("0");
        }
    }
}

struct Point {
    x: i32,
    y: i32,
}

struct Edge {
    u: usize,
    v: usize,
}
