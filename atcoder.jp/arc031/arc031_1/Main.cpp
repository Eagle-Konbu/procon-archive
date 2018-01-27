#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;

int main(){
	string S;
	cin >> S;

	bool ok = true;
	for(int i=0; i<S.size(); i++){
		if(S[i] != S[S.size()-i-1]) ok = false;
	}

	cout << (ok ? "YES" : "NO") << endl;

	return 0;
}
