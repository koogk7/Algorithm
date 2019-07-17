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

/* 17143 낚시왕
 * 회고
 *  - 인덱스가 필요할 때는 벡터의 인덱스를 사용 이를 box에다 저장하는 식으로 사용하자
 *  - 코드 로직이 복잡해지면 무언가 실수를 하고 있는거다 다시 생각해보자
 *  - 방향과 경계범위를 같이 생각해야한다.
 *  - 경계에서 갈 수 없는 방향을 가지고 있는 상어가 있을 수 있기때문에 처음에 범위체크를 한번 하고 들어가야 한다.
 *  - 요거 한번 더 풀어보자
 */

#define MAX_N 103

int r,c,m;
int box[MAX_N][MAX_N]; // 상어 번호 저장
struct shark{
    int idx;
    int row, col;
    int speed, driect, size;
    bool isAlive;
};
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,1,-1};
vector<shark> sharkList;



bool isRowBoundary (int target, int dir){
    return (target == r-1  && dir == 2)|| (target == 0 && dir == 1);
}

bool isColBoundary (int target, int dir){
    return (target == c-1 &&  dir == 3) || (target == 0 && dir == 4);
}



int reverseDir(int d){
    if(d == 1) return 2;
    if(d == 2) return 1;
    if(d == 3) return 4;
    else return 3;
}

int catchShark(int postion){
    for (int row = 0; row < r; ++row) {
        if(box[row][postion] != -1){
            sharkList[box[row][postion]].isAlive = false;
            int rst = sharkList[box[row][postion]].size;
            box[row][postion] = -1;
            return rst;
        }
    }
    return 0;
}

int battleShark(int shark1, int shark2){
    if(sharkList[shark1].size < sharkList[shark2].size) {
        sharkList[shark1].isAlive = false;
        return shark2;
    }
    sharkList[shark2].isAlive = false;
    return shark1;
}

void moveOneShark(shark target){
    int d = target.driect;
    int nextRow = target.row;
    int nextCol = target.col;
    int speed = target.speed;

    if(d < 3 && isRowBoundary(nextRow, d))
        d = reverseDir(d);
    if(d > 2 && isColBoundary(nextCol, d))
        d = reverseDir(d);

    while(speed--){
        nextRow += dr[d-1];
        nextCol += dc[d-1];
        if(d < 3 && isRowBoundary(nextRow, d))
            d = reverseDir(d);
        if(d > 2 && isColBoundary(nextCol, d))
            d = reverseDir(d);
    }

    if(box[nextRow][nextCol] != -1){
        int winShark = battleShark(box[nextRow][nextCol], target.idx);
        box[nextRow][nextCol] = winShark;
        sharkList[winShark].row = nextRow;
        sharkList[winShark].col = nextCol;
    } else {
        box[nextRow][nextCol] = target.idx;
    }
    sharkList[target.idx].row = nextRow;
    sharkList[target.idx].col = nextCol;
    sharkList[target.idx].driect = d;

}

void moveSharks(){

    for (int i = 0; i < sharkList.size(); ++i) {
        if(!sharkList[i].isAlive) continue;
        moveOneShark(sharkList[i]);
    }
}

void Init(){
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            box[i][j] = -1;
        }
    }
}

void Display(){
    cout << "================" << endl;

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cout << box[i][j]+1 << " ";
        }
        cout << "\n";
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int ans = 0;
    cin >> r >> c >> m;

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            box[i][j] = -1;
        }
    }

    int row, col, speed, direct, size;

    for (int i = 0; i < m; ++i) {
        cin >> row >> col >> speed >> direct >> size;
        sharkList.push_back({i, row-1,col-1,speed,direct,size,true});
        box[row-1][col-1] = i ; // 상어번호
    }

    for (int k = 0; k < c; ++k) {
        ans += catchShark(k);
//        Display();
        Init();
        moveSharks();
    }

    cout << ans << "\n";
}

