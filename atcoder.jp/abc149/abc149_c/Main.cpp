#include<bits/stdc++.h>
#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;
using ll = long long;
using P = pair<int, int>;

bool fact(int x) {
    for(int i = 2; i < sqrt(x); i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int x;
    cin >> x;

    if(fact(x)){
        cout << x << endl;
        return 0;
    }

    while (true) {
        x++;
        if (fact(x)) {
            cout << x << endl;
            return 0;
        }
    }
}