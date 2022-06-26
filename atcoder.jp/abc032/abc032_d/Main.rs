use std::vec;

use itertools::Itertools;
use proconio::input;
use rand::Rng;

fn main() {
    // let mut timer = Timer::new();

    // for n in 1..=200 {
    //     let mut items = Item::generate_items(n, 1000, 1000);
    //     let capacity = 5000;

    //     // timer.reset();
    //     // let ans1 = brute_force(&items, 500);
    //     // let time1 = timer.get_time();

    //     let mut ans = 0;
    //     timer.reset();
    //     branch_bound(&mut items, capacity, &mut ans, false);
    //     let ans2 = ans.clone();
    //     let time2 = timer.get_time();

    //     timer.reset();
    //     branch_bound(&mut items, capacity, &mut ans, true);
    //     let ans3 = ans.clone();
    //     let time3 = timer.get_time();

    //     timer.reset();
    //     nailing_test(&mut items, capacity, &mut ans);
    //     let time4 = timer.get_time();
    //     let ans4 = ans.clone();

    //     // println!(
    //     //     "n:{}, ans2:{}, time2:{}s, ans3:{}, time3:{}s, ans4:{}, time4:{}s",
    //     //     n, ans2.1, time2, ans3.1, time3, ans4.1, time4
    //     // );
    //     println!(
    //         "n:{}, time2:{}s, time3:{}s, time4:{}s",
    //         n, time2, time3, time4
    //     );
    // }

    // for atcoder
    input! {
        n: usize,
        w: i64,
        vw:[(i64,i64);n]
    };
    let mut items: Vec<Item> = vw.into_iter().map(|(v, w)| Item::new(v, w)).collect();
    let mut ans = greedy(&items, w).1;
    // branch_bound(&mut items, w, &mut ans, true);
    nailing_test(&mut items, w, &mut ans);
    println!("{}", ans);
}

fn brute_force(items: &Vec<Item>, capacity: i64) -> (Vec<&Item>, i64) {
    let n = items.len();

    let mut ans = (vec![], 0);

    for i in 1..=n {
        for comb in items.iter().combinations(i) {
            let sum_weight: i64 = comb.iter().map(|&&x| x.weight).sum();
            let sum_value: i64 = comb.iter().map(|&&x| x.value).sum();

            if ans.1 < sum_value && sum_weight <= capacity {
                ans = (comb, sum_value);
            }
        }
    }

    return ans;
}

fn branch_bound(
    items: &mut Vec<Item>,
    capacity: i64,
    provisional_opt_value: &mut i64,
    cut_branch: bool,
) {
    let lp_relax_result = lp_relax(items, capacity);

    let mut not_integer_idx = !0;
    for (i, &x) in lp_relax_result.0.iter().enumerate() {
        if x != 0.0 && x != 1.0 {
            not_integer_idx = i;
            break;
        }
    }

    if not_integer_idx == !0 {
        if *provisional_opt_value < lp_relax_result.1 as i64 {
            *provisional_opt_value = lp_relax_result.1 as i64;
        }
        return;
    }

    if cut_branch {
        if (lp_relax_result.1.floor() as i64) < *provisional_opt_value {
            return;
        }
    }

    let used_capacity = items
        .iter()
        .filter(|&item| item.used == 1)
        .map(|&item| item.weight)
        .sum::<i64>();

    items[not_integer_idx].used = 0;
    branch_bound(items, capacity, provisional_opt_value, cut_branch);

    if used_capacity + items[not_integer_idx].weight <= capacity {
        items[not_integer_idx].used = 1;
        branch_bound(items, capacity, provisional_opt_value, cut_branch);
    }

    items[not_integer_idx].used = -1;
}

fn lp_relax(items: &Vec<Item>, capacity: i64) -> (Vec<f64>, f64) {
    let sorted_iter = items
        .iter()
        .enumerate()
        .filter(|(_, &item)| item.used == -1)
        .sorted_by(|(_, &item1), (_, &item2)| {
            let eff1 = item1.value as f64 / item1.weight as f64;
            let eff2 = item2.value as f64 / item2.weight as f64;
            eff1.partial_cmp(&eff2).unwrap()
        })
        .rev();

    let mut ans = (vec![0.0; items.len()], 0.0);
    let mut remaining_capacity = capacity as f64;

    for (idx, &item) in items.iter().enumerate() {
        if remaining_capacity == 0.0 {
            break;
        }
        if item.used == 1 {
            ans.0[idx] = 1.0;
            remaining_capacity -= item.weight as f64;
            ans.1 += item.value as f64;
        }
    }

    if remaining_capacity < 0.0 {
        return (ans.0, -1.0);
    }

    for (index, &item) in sorted_iter {
        let usage = (item.weight as f64).min(remaining_capacity);
        remaining_capacity -= usage;
        ans.0[index] = usage / item.weight as f64;
        ans.1 += item.value as f64 * ans.0[index];

        if remaining_capacity == 0.0 {
            break;
        }
    }
    return ans;
}

fn greedy(items: &Vec<Item>, capacity: i64) -> (Vec<i32>, i64) {
    let sorted_iter = items
        .iter()
        .enumerate()
        .sorted_by(|(_, &item1), (_, &item2)| {
            let eff1 = item1.value as f64 / item1.weight as f64;
            let eff2 = item2.value as f64 / item2.weight as f64;
            eff1.partial_cmp(&eff2).unwrap()
        })
        .rev();

    let mut ans = (vec![0; items.len()], 0);
    let mut remaining_capacity = capacity;

    for (index, &item) in sorted_iter {
        if remaining_capacity >= item.weight {
            remaining_capacity -= item.weight;
            ans.0[index] = 1;
            ans.1 += item.value;
        }
    }
    return ans;
}

fn nailing_test(items: &mut Vec<Item>, capacity: i64, ans: &mut i64) {
    let lp_relax_result = lp_relax(items, capacity);

    let mut not_integer_idx = !0;
    for i in 0..items.len() {
        if lp_relax_result.0[i] != lp_relax_result.0[i].round() {
            not_integer_idx = i;
            break;
        }
    }

    if not_integer_idx == !0 {
        *ans = lp_relax_result.1 as i64;
        return;
    }

    let greedy_result = greedy(items, capacity).1 as f64;

    let mut nail = vec![-1; items.len()];

    for flg in 0..=1 {
        items[not_integer_idx].used = flg;
        let lp_relax_val = lp_relax(items, capacity).1;
        items[not_integer_idx].used = -1;

        if lp_relax_val < greedy_result {
            nail[not_integer_idx] = 1 - flg;
        }
    }

    for i in 0..items.len() {
        if i == not_integer_idx {
            continue;
        }

        if lp_relax_result.0[i] == 1.0 {
            items[i].used = 0;
        } else {
            items[i].used = 1;
        }

        let lp_relax_val = lp_relax(items, capacity).1;
        items[i].used = -1;

        if lp_relax_val < greedy_result {
            nail[i] = if lp_relax_result.0[i] == 1.0 { 1 } else { 0 };
        }
    }

    for i in 0..items.len() {
        items[i].used = nail[i];
    }

    branch_bound(items, capacity, ans, true);
}

#[derive(Debug, Clone, Copy)]
struct Item {
    value: i64,
    weight: i64,
    used: i32,
}

impl Item {
    fn new(value: i64, weight: i64) -> Item {
        Item {
            value,
            weight,
            used: -1,
        }
    }

    // fn generate_items(n: usize, max_weight: i64, max_value: i64) -> Vec<Item> {
    //     let mut rng = rand::thread_rng();

    //     let weight_scale = std::cmp::min(1, i64::MAX / max_weight / (n as i64));
    //     let value_scale = std::cmp::min(1, i64::MAX / max_value / (n as i64));

    //     let res = (0..n)
    //         .map(|_| {
    //             let value = rng.gen_range(1..=max_value);
    //             let weight = rng.gen_range(1..=max_weight);

    //             Item::new(value * value_scale, weight * weight_scale)
    //         })
    //         .collect();

    //     return res;
    // }
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
        self.start_time = get_time();
    }
}
