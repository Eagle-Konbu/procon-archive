use proconio::input;

fn dfs(g: &Vec<Vec<usize>>, v: usize, p: usize, dep_list: &mut Vec<i32>, dep: i32) {
    dep_list[v] = dep;
    for &u in g[v].iter() {
        if u == p {
            continue;
        }
        dfs(&g, u, v, dep_list, dep + 1);
    }
}

fn main() {
    input! {
        n:usize,
        q:usize,
        ab:[(usize,usize);n-1],
        cd:[(usize,usize);q]
    };

    let mut g = vec![vec![]; n];
    let mut dep_list = vec![0; n];

    for &(a, b) in ab.iter() {
        g[a - 1].push(b - 1);
        g[b - 1].push(a - 1);
    }

    dfs(&g, 0, n, &mut dep_list, 0);

    for &(c,d) in cd.iter() {
        if (dep_list[c-1] + dep_list[d-1]) % 2 == 0 {
            println!("Town");
        } else {
            println!("Road");
        }
    }
}
