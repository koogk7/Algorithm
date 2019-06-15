// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;


/**
 * 1938번 통나무 옮기기
 *
 *  회고
 *
 *  0. 생각보다 까다로웠던 문제다. 처음 생각보다 조건이 걸리는 부분들이 많고 로직이 꼬이기 쉬운 부분이
 *  많은 거같다. 코드양이 많아질 때는 반드시 모듈별 테스트를 진행하고, 코드가 복잡해지는 기미가 보이면
 *  모듈로 빼서, 핵심로직에 혼란이 가지 않게 하자! 모듈을 만들면 모듈테스트는 반드시 진행하자!
 *
 *  1. 구조체 설정에 초반에 미스가 있었다. mode는 따로 좌표를 저장해서 진행하면 코드가
 *  복잡해짐으로 0,1 flag 형식으로 저장해서 사용했다 ---> 다음부터 토글은 boolean 형식을 이용하자
 *
 *  2. isNext부분을 초기 구상시에 놓쳤다. 다행히 함수 단위별 테스트가 잘 이루어져 어느 부분을 놓치고
 *  어떤 부분이 에러가 있는지 쉽게 찾을 수 있었다.
 *
 *  3.통나무를 중심좌표만으로 컨트롤하는데 이동여부 검사시에는 3개 다 체크해야한다. 이 부분에서 첫번째
 *  실수가 있었고 3개 체크할 때 for문 범위를 잘못 지정해서 마지막 로우나 컬럼을 검사하지 않고 있었다.
 *  for문 범위 지정에 신경쓰자!
 *
 *  4.if문 안 boolean 조건식을 반대로 해주고 있었다. 디버깅은 콘솔로 찍어보면서 따라가보자. 3차원일
 *  경울 2차원으로 출력하되 그 안에 내용은 ( , )으로 감싸서 출력하자. 출력이 곧 최고의 디버깅이다.
 *
 */


int n;
int map[51][51];
int visit[51][51][2];
int dr[5] = {-1,1,0,0,0};
int dc[5] = {0,0,-1,1,0};
int ans;
struct center{
    int row, col, mode;
};
queue<center>que;
center start;
center end_point;


void Display(string msg){
    cout << "==========" << msg << "==========="<< endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout <<"("<< visit[i][j][0] << "," << visit[i][j][1] << ") ";
        }
        cout << endl;
    }
}

bool isBoundary(int r, int c){
    return r < n && r >= 0 && c < n && c >= 0;
}

bool isEnd(center cur){

    return cur.row == end_point.row
            && cur.col == end_point.col
            && cur.mode == end_point.mode;
}

bool isTurn(center cur){
    for (int i = cur.row-1; i < cur.row+2; ++i) {
        for (int j = cur.col-1; j < cur.col+2; ++j) {
            if(!isBoundary(i,j)) return false;
            if(map[i][j] == 1) return false;
        }
    }
    return true;
}

bool isNext(center cur){
    if(cur.mode == 0){ // 세로
        for (int i = cur.row-1; i < cur.row+2; ++i) {
            if(!isBoundary(i,cur.col)) return false;
            if(map[i][cur.col] == 1) return false;
        }
        return true;
    }

    for (int i = cur.col-1; i < cur.col+2; ++i) {
        if(!isBoundary(cur.row,i)) return false;
        if(map[cur.row][i] == 1) return false;
    }
    return true;

}

int modeToggle(int mode){
    return mode == 0 ? 1 : 0;
}

int BFS(){
    while (!que.empty()){
        int row = que.front().row;
        int col = que.front().col;
        int mode = que.front().mode;
        que.pop();

        int depth = visit[row][col][mode] + 1;

        for (int i = 0; i < 5; ++i) {
            int nr = row + dr[i];
            int nc = col + dc[i];
            int toggle = modeToggle(mode);
            if(isEnd({nr,nc,mode})) return depth;
            if(i == 4 && visit[nr][nc][toggle] == 0){
                if(!isTurn({nr, nc, mode})) continue;
                que.push({nr, nc, toggle});
                visit[nr][nc][toggle] = depth;
                continue;
            }
            if(!isBoundary(nr,nc)) continue;
            if(visit[nr][nc][mode] != 0) continue;
            if(!isNext({nr,nc,mode})) continue;
            que.push({nr, nc, mode});
            visit[nr][nc][mode] = depth;
        }
    }
    return 1;
}

int getMode(center cur){
    if(!isBoundary(cur.row,cur.col+1)
        || map[cur.row][cur.col+1] == 0
        || map[cur.row][cur.col+1] == 1)
        return 0; // 세로

    return 1; // 가로
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int findB = 0, findE = 0;

    cin >> n;
    char trans;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> trans;
            if(trans == 'B'){
                findB++;
                map[i][j] = 2;
                if(findB == 2)
                    start = {i,j};
            } else if(trans == 'E'){
                findE++;
                map[i][j] = 3;
                if(findE == 2)
                    end_point = {i,j};
            } else{
                map[i][j] = trans - '0';
            }
        }
    }
    start.mode = getMode(start);
    end_point.mode = getMode(end_point);


    que.push(start);
    visit[start.row][start.col][start.mode] = 1;

    ans = BFS();
//    Display("Display");

//    cout << start.mode_row << ", "<< start.mode_col << endl;
//    cout << end_point.mode_row << ", "<< end_point.mode_col << endl;

    cout << ans - 1 << endl;

}

