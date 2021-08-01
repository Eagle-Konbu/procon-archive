use proconio::input;
use std::cmp;

pub trait BinarySearch<T> {
    fn lower_bound(&self, x: &T) -> usize;
    fn upper_bound(&self, x: &T) -> usize;
}
impl<T: Ord> BinarySearch<T> for [T] {
    fn lower_bound(&self, x: &T) -> usize {
        let mut ng = -1isize;
        let mut ok = self.len() as isize;
        while ok - ng > 1 {
            let mid = ng + (ok - ng) / 2;
            match self[mid as usize].cmp(x) {
                std::cmp::Ordering::Greater | std::cmp::Ordering::Equal => ok = mid,
                std::cmp::Ordering::Less => ng = mid,
            }
        }
        ok as usize
    }
    fn upper_bound(&self, x: &T) -> usize {
        let mut ng = -1isize;
        let mut ok = self.len() as isize;
        while ok - ng > 1 {
            let mid = ng + (ok - ng) / 2;
            match self[mid as usize].cmp(x) {
                std::cmp::Ordering::Greater => ok = mid,
                std::cmp::Ordering::Less | std::cmp::Ordering::Equal => ng = mid,
            }
        }
        ok as usize
    }
}

fn main() {
    input! {
        n:usize,
        m:usize,
        mut a:[i32;n],
        mut b:[i32;m]
    };

    let mut min = std::i32::MAX;

    a.sort();
    b.sort();

    for &a_tmp in a.iter() {
        let idx = b.lower_bound(&a_tmp);
        if idx < m {
            min = cmp::min(min, (a_tmp - b[idx]).abs());
        }
        if idx >= 1 {
            min = cmp::min(min, (a_tmp - b[idx - 1]).abs());
        }
    }

    println!("{}", &min);
}
