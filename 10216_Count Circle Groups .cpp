#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
/*
 * i번째 통신탑은 여기서부터 ri이내 거리에 있는 모든 지역을 자신의 통신영역으로 가진다
 * 통신영역이 겹치는 부분이 있다면 이 둘은 직접 통신이 가능
 * 몇 개의 직접 통신을 거쳐 최종적으로 통신이 가능하다면 통신이 가능!
 * 통신이 가능한 그룹의 갯수를 알아내
 * * */


using namespace std;


struct camp{
    int x, y, d;
};
int t,n = 1;
camp enemy[3002];
int parent[3002];


bool isAdjust(camp a1, camp a2)
{
    bool rst = false;
    int x = a1.x-a2.x;
    int y = a1.y-a2.y;
    int r = a1.d + a2.d;
    int dist = x*x + y*y;
    if(dist <= r*r) rst = true;

    return rst;

}

int Find(int x){
    if(parent[x] == x) return x;
    return parent[x] = Find(parent[x]);
}

void merge(int x, int y){
    x = Find(x);
    y = Find(y);

    if(x != y){
        parent[x] = y;
    }
    else return;
}

int main(){

    cin >> t;

   while(t--){
       cin >> n;


       for (int i = 0; i < n; ++i) {
           cin >> enemy[i].x >> enemy[i].y>>enemy[i].d;
           parent[i] = i;
       }

       int cnt = n;
       for (int i = 0; i < n; ++i) {
           for (int j = i+1; j < n ; ++j) {
                if(!isAdjust(enemy[i],enemy[j])) continue;
                if(Find(i) == Find(j)) continue;
                merge(i,j);
                cnt--;
           }
       }

       cout << cnt << endl;

   }

}

