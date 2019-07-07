// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
#include <map>
#include <math.h>
using namespace std;


/**
 * 16236번 아기상어
 *
 *  회고
 * 1. 물고기 크기가 같을 때 먹는 순서를 잘못 인지하고 있었다.
 * 2. 더 최적의 조건이 있음에도 먹을 수 있는 물고기를 찾으면, 같은 레벨의 다른 물고기를 검사하지 않고 바로 리턴했다.
 * 3. 물고기 검사하고나서 dist를 + 1 해줬다.
 * 4. 메소드를 최대한 잘게 단일책임을 지키게 분리하자! 그래야 디버깅이 편하다.
 */

struct shark{
    int row, col;
    int age;
    int exp;
};
struct fish{
    int row, col;
};
int sea[21][21];
int visit[21][21];
int dr[4] = {-1,0,0,1};
int dc[4] = {0,-1,1,0};
int n, sec;
shark baby = {0,0,2,0};

bool isBoundary(int row, int col){
    return row < n && row >= 0 && col < n && col >= 0;
}

bool isMove(int value){
    return value <= baby.age;
}
bool isEat(int value){
    return (value != 0) && (value < baby.age);
}

void moveShark(int row, int col){
    baby.row = row;
    baby.col = col;
}

void eatFish(int row, int col){
    baby.exp++;
    if(baby.exp == baby.age){
        baby.age++;
        baby.exp = 0;
    }
    sea[row][col] = 0;
}

void initVisit(){
    memset(visit,0,sizeof(visit));
}

bool isUpdateFish(fish candi, fish newFish){
    if(newFish.row < candi.row) return true;
    return newFish.row == candi.row
           && newFish.col < candi.col;

}

void Display(){
    cout << "=======================" << endl;
    cout << "row : " << baby.row << " col : " << baby.col
         << " age : " << baby.age << " exp : " << baby.exp << " sec : " << sec <<endl;
    sea[baby.row][baby.col] = 9;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << sea[i][j] << " ";
        }
        cout << endl;
    }
    sea[baby.row][baby.col] = 0;
}

bool findEating(){
    int row, col, dist;
    queue<fish> que;
    que.push({baby.row, baby.col});
    fish candi = {n+1,n+1};
    bool canEat = false;


    while(!que.empty()){
        row = que.front().row;
        col = que.front().col;
        que.pop();


        dist = visit[row][col] + 1;
        if(canEat && visit[candi.row][candi.col] < dist ) continue;

        for (int i = 0; i < 4; ++i) {
            int nr = dr[i] + row;
            int nc = dc[i] + col;
            if(!isBoundary(nr,nc)) continue;
            if(visit[nr][nc] != 0) continue;
            if(!isMove(sea[nr][nc])) continue;
            if(isEat(sea[nr][nc])){
                if(isUpdateFish(candi, {nr,nc}))
                    candi = {nr,nc};
                canEat = true;
            }
            visit[nr][nc] = dist;
            if(canEat) continue;
            que.push({nr,nc});
        }
    }

    if(canEat){
        moveShark(candi.row, candi.col);
        eatFish(candi.row, candi.col);
        sec += visit[candi.row][candi.col];
        return true;
    }

    return false;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);



    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> sea[i][j];
            if(sea[i][j] == 9){
                baby.row = i;
                baby.col = j;
                sea[i][j] = 0;
            }
        }
    }

    while(findEating())
        initVisit();
//    cout << "=====ans====" << endl;
    cout << sec << endl;

}

