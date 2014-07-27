#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cctype>
#include<cstdlib>
#include<cmath>
#include<list>
#include<string>
#include<stack>
#include<queue>
#include<deque>
#define MAX_N 1030
using namespace std;
struct st{
	int x;
	int y;
};
int n=0;
int w=0;
int h=0;
st star[100];
int countt=0;
int main(){
	cin>>n>>w>>h;
	for(int i=1;i<=n;i++){
		cin>>star[i].x>>star[i].y;
	}
	for(int a=1;a<=n;a++){
		for(int b=1;b<=n;b++){
			if(a==b){
				continue;
			}
			for(int c=1;c<=n;c++){
				if(a==c||b==c){
					continue;
				}
				for(int d=1;d<=n;d++){
					if(a==d||b==d||c==d){
						continue;
					}
					double ab=sqrt(pow((double)(abs(star[a].x-star[b].x)),(double)2)+pow((double)(abs(star[a].y-star[b].y)),(double)2));
					double cd=sqrt(pow((double)(abs(star[c].x-star[d].x)),(double)2)+pow((double)(abs(star[c].y-star[d].y)),(double)2));
					if(star[a].x+ab>w||star[a].x-ab<0||star[a].y+ab>h||star[a].y-ab<0){
						continue;
					}
					if(star[c].x+cd>w||star[c].x-cd<0||star[c].y+cd>h||star[c].y-cd<0){
						continue;
					}
					ab=pow((double)(abs(star[a].x-star[b].x)),(double)2)+pow((double)(abs(star[a].y-star[b].y)),(double)2);
				    cd=pow((double)(abs(star[c].x-star[d].x)),(double)2)+pow((double)(abs(star[c].y-star[d].y)),(double)2);
					double ac=pow((double)(abs(star[a].x-star[c].x)),(double)2)+pow((double)(abs(star[a].y-star[c].y)),(double)2);
					if(cd-ab-ac<0){
						continue;
					}
					if(4*ac*ab<pow((cd-ab-ac),(double)2)){
						countt++;
					}
				}
			}
		}
	}
	printf("%lld",countt);
	cout<<endl;
	cin.get();
	cin.get();
	return 0;
}