use proconio::{input, source::line::LineSource};
use rand::Rng;
use std::{
    collections::VecDeque,
    io::{self, BufReader},
};

const TIME_LIMIT: f64 = 2.5;

#[derive(Debug, Clone, Copy)]
enum PetType {
    Cow,
    Pig,
    Rabbit,
    Dog,
    Cat,
}

#[derive(Debug, Clone, Copy, PartialEq)]
enum UpOrDown {
    Down,
    Up,
}

#[derive(Debug, Clone, Copy)]
struct Point {
    x: i64,
    y: i64,
    disabled: bool,
}

#[derive(Debug, Clone, Copy)]
struct Pet {
    position: Point,
    pet_type: PetType,
}

#[derive(Debug, Clone, Copy)]
struct Human {
    position: Point,
    visited_bound: bool,
    is_to_start: bool,
    finished: bool,
    index: isize,
    up_or_down: UpOrDown,
}

fn main() {
    // let args: Vec<String> = std::env::args().collect();

    let mut stdin = LineSource::new(BufReader::new(io::stdin()));
    macro_rules! input(($($tt:tt)*) => (proconio::input!(from &mut stdin, $($tt)*)));

    input! {
        n:usize,
        pxyt: [(i64,i64,usize);n],
        m:usize,
        hxy: [(i64,i64);m]
    };

    let mut disabled = vec![vec![false; 30]; 30];

    let mut pets = pxyt
        .iter()
        .map(|&(x, y, t)| {
            let p_type = match t {
                1 => PetType::Cow,
                2 => PetType::Pig,
                3 => PetType::Rabbit,
                4 => PetType::Dog,
                5 => PetType::Cat,
                _ => PetType::Cow,
            };
            return Pet {
                position: Point::new(x - 1, y - 1),
                pet_type: p_type,
            };
        })
        .collect::<Vec<Pet>>();
    let mut humans = hxy
        .iter()
        .map(|&(x, y)| Human {
            position: Point::new(x - 1, y - 1),
            visited_bound: false,
            is_to_start: false,
            index: -1,
            finished: false,
            up_or_down: UpOrDown::Down,
        })
        .collect::<Vec<Human>>();

    let mut cnt = 0;
    for y in 0..30 {
        for human in humans.iter_mut() {
            if human.position.y == y {
                human.index = cnt;
                cnt += 1;
            }
        }
    }

    for h in humans.iter_mut() {
        if h.position.x == 0 {
            h.visited_bound = true;
            h.up_or_down = UpOrDown::Down;
        }
        if h.position.x == 29 {
            h.visited_bound = true;
            h.up_or_down = UpOrDown::Up;
        }
        let target_y = ((30.0 / (m + 1) as f64) * ((h.index + 1) as f64)).round() as i64;
        if h.position.y == target_y {
            h.is_to_start = true;
        }
    }

    for _ in 0..300 {
        let mut action = String::from("");
        for i in 0..humans.len() {
            let all_ready = humans.iter().all(|h| h.is_to_start);
            let all_finished = humans.iter().all(|h| h.finished);
            if humans[i].finished {
                let target = Point::new(humans[i].position.x, humans[i].position.y - 1);
                if disabled[target.x as usize][target.y as usize] {
                    action += ".";
                } else {
                    if can_be_disabled(target, &humans, &pets, &disabled, i)
                        && !in_clean_area(&humans[i], &pets, &disabled)
                    {
                        let current_score = calc_score(&humans, &pets, &disabled);
                        disable(target, &mut disabled);
                        let new_score = calc_score(&humans, &pets, &disabled);
                        if new_score <= current_score {
                            enable(target, &mut disabled);
                            action += ".";
                        } else {
                            action += "l";
                        }
                    } else {
                        action += ".";
                    }
                }
                continue;
            }
            if !humans[i].visited_bound {
                if humans[i].position.x < 15 {
                    humans[i].position.x -= 1;
                    action += "U";
                    if humans[i].position.x == 0 {
                        humans[i].visited_bound = true;
                        humans[i].up_or_down = UpOrDown::Down;
                    }
                } else {
                    humans[i].position.x += 1;
                    action += "D";
                    if humans[i].position.x == 29 {
                        humans[i].visited_bound = true;
                        humans[i].up_or_down = UpOrDown::Up;
                    }
                }
                continue;
            } else if !humans[i].is_to_start {
                let target_y =
                    ((30.0 / (m + 1) as f64) * ((humans[i].index + 1) as f64)).round() as i64;
                let dir = (target_y - humans[i].position.y).signum();
                humans[i].position.y += 1 * dir;
                action += if dir < 0 {
                    "L"
                } else if dir == 0 {
                    "."
                } else {
                    "R"
                };
                if humans[i].position.y == target_y {
                    humans[i].is_to_start = true;
                }
                // println!("#{} {}", humans[i].index, target_y);
                continue;
            }

            if !all_ready {
                action += ".";
                continue;
            }

            let target = Point::new(humans[i].position.x, humans[i].position.y - 1);
            if target.x < 0 || target.y < 0 {
                action += ".";
                continue;
            }
            if !disabled[target.x as usize][target.y as usize] {
                if can_be_disabled(target, &humans, &pets, &disabled, i) {
                    disable(target, &mut disabled);
                    action += "l";
                    continue;
                } else {
                    action += ".";
                    continue;
                }
            }

            if humans[i].up_or_down == UpOrDown::Down {
                if disabled[humans[i].position.x as usize + 1][humans[i].position.y as usize] {
                    action += ".";
                    continue;
                }
                humans[i].position.x += 1;
                action += "D";
            } else {
                if disabled[humans[i].position.x as usize - 1][humans[i].position.y as usize] {
                    action += ".";
                    continue;
                }
                humans[i].position.x -= 1;
                action += "U";
            }

            if humans[i].position.x == 0 || humans[i].position.x == 29 {
                humans[i].finished = true;
            }
        }

        for i in 0..humans.len() {
            let human_pos = humans[i].position;

            let up = Point::new(human_pos.x - 1, human_pos.y);
            let down = Point::new(human_pos.x + 1, human_pos.y);
            let left = Point::new(human_pos.x, human_pos.y - 1);
            let right = Point::new(human_pos.x, human_pos.y + 1);

            let c = action.chars().nth(i).unwrap();
            let mut adj = up;
            if c == 'l' {
                adj = left;
            } else if c == 'r' {
                adj = right;
            } else if c == 'u' {
                adj = up;
            } else if c == 'd' {
                adj = down;
            } else {
                continue;
            }

            // let current_score = calc_score(&humans, &pets, &disabled);
            enable(adj, &mut disabled);
            if !in_clean_area(&humans[i],&pets, &disabled) {
                disable(adj, &mut disabled);
            } else {
                action.replace_range(i..(i + 1), ".");
            }
            // let new_score = calc_score(&humans, &pets, &disabled);
            // if new_score <= current_score {
            //     disable(adj, &mut disabled);
            // } else {
            //     action.replace_range(i..(i + 1), ".");
            // }
        }

        println!("{}", action);

        input! {
            pet_actions: [String; n]
        };

        for (pet, pet_action) in itertools::zip(pets.iter_mut(), pet_actions) {
            for i in 0..pet_action.len() {
                let a = pet_action.chars().nth(i).unwrap();
                if a == '.' {
                    continue;
                }
                move_pet(pet, a);
            }
        }
    }
}

fn in_clean_area(human: &Human, pets: &Vec<Pet>, disabled: &Vec<Vec<bool>>) -> bool {
    let mut seen = vec![vec![false; 30]; 30];
    let mut que = VecDeque::new();

    que.push_back(human.position);
    seen[human.position.x as usize][human.position.y as usize] = true;

    while !que.is_empty() {
        let current = que.pop_front().unwrap();

        let up = Point::new(current.x - 1, current.y);
        let down = Point::new(current.x + 1, current.y);
        let left = Point::new(current.x, current.y - 1);
        let right = Point::new(current.x, current.y + 1);
        for &p in vec![up, down, left, right].iter() {
            if p.x < 0 || p.x >= 30 || p.y < 0 || p.y >= 30 {
                continue;
            }
            if disabled[p.x as usize][p.y as usize] {
                continue;
            }
            if seen[p.x as usize][p.y as usize] {
                continue;
            }

            for &pet in pets.iter() {
                if p.x == pet.position.x && p.y == pet.position.y {
                    return false;
                }
            }

            que.push_back(p);
            seen[p.x as usize][p.y as usize] = true;
        }
    }

    return true;
}

fn calc_score(humans: &Vec<Human>, pets: &Vec<Pet>, disabled: &Vec<Vec<bool>>) -> i64 {
    let m = humans.len();
    let mut score = 0.0;

    for i in 0..m {
        let mut seen = vec![vec![false; 30]; 30];
        let mut r = vec![];
        let mut que = VecDeque::new();

        que.push_back(humans[i].position);
        seen[humans[i].position.x as usize][humans[i].position.y as usize] = true;

        while !que.is_empty() {
            let current = que.pop_front().unwrap();
            r.push(current);

            let up = Point::new(current.x - 1, current.y);
            let down = Point::new(current.x + 1, current.y);
            let left = Point::new(current.x, current.y - 1);
            let right = Point::new(current.x, current.y + 1);
            for &p in vec![up, down, left, right].iter() {
                if p.x < 0 || p.x >= 30 || p.y < 0 || p.y >= 30 {
                    continue;
                }
                if disabled[p.x as usize][p.y as usize] {
                    continue;
                }
                if seen[p.x as usize][p.y as usize] {
                    continue;
                }
                que.push_back(p);
                seen[p.x as usize][p.y as usize] = true;
            }
        }

        let mut n = 0;
        for &pet in pets.iter() {
            for &point in r.iter() {
                if pet.position.x == point.x && pet.position.y == point.y {
                    n += 1;
                }
            }
        }
        score += (r.len() as f64 / 900.0) * 2.0f64.powi(-n);
    }

    return (1e8 * score / (m as f64)).round() as i64;
}

fn disable(point: Point, disabled: &mut Vec<Vec<bool>>) {
    disabled[point.x as usize][point.y as usize] = true;
}

fn enable(point: Point, disabled: &mut Vec<Vec<bool>>) {
    disabled[point.x as usize][point.y as usize] = false;
}

fn move_pet(pet: &mut Pet, direction: char) {
    let mut target = pet.position;
    match direction {
        'U' => target.x -= 1,
        'D' => target.x += 1,
        'L' => target.y -= 1,
        'R' => target.y += 1,
        _ => println!("wa-wa-wa"),
    };

    pet.position = target;
}

fn can_be_disabled(
    target: Point,
    humans: &Vec<Human>,
    pets: &Vec<Pet>,
    disabled: &Vec<Vec<bool>>,
    human_idx: usize,
) -> bool {
    let x = target.x;
    let y = target.y;

    if x < 0 || x >= 30 || y < 0 || y >= 30 {
        return false;
    }

    for (i, &h) in humans.iter().enumerate() {
        if i == human_idx {
            continue;
        }
        if x == h.position.x && y == h.position.y {
            return false;
        }
        if x + 1 == h.position.x && y == h.position.y && !h.finished {
            return false;
        }
        if x - 1 == h.position.x && y == h.position.y && !h.finished {
            return false;
        }
        if x == h.position.x && y + 1 == h.position.y && !h.finished {
            return false;
        }
        if x == h.position.x && y - 1 == h.position.y && !h.finished {
            return false;
        }
    }
    for &p in pets.iter() {
        if x == p.position.x && y == p.position.y {
            return false;
        }
        if x + 1 == p.position.x && y == p.position.y {
            return false;
        }
        if x - 1 == p.position.x && y == p.position.y {
            return false;
        }
        if x == p.position.x && y + 1 == p.position.y {
            return false;
        }
        if x == p.position.x && y - 1 == p.position.y {
            return false;
        }
    }

    if disabled[x as usize][y as usize] {
        return false;
    }

    return true;
}

impl Point {
    fn new(x: i64, y: i64) -> Point {
        Point {
            x,
            y,
            disabled: false,
        }
    }
}

fn prob_sa(delta: f64, temperture: f64) -> f64 {
    if delta >= 0.0 {
        return 1.0;
    } else {
        return (delta / temperture).exp();
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
