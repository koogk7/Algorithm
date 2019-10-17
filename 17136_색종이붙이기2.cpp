// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
#include <map>
#include <math.h>
#include <stack>
#include <set>
#include <sstream>
#include <string.h>
using namespace std;
typedef long long ll;
#define INF 987654321
/*
 *  17136 색종이 붙이기
 *  1이 적힌 칸은 모두 색동이로 덮여야 한다.
 *  색종이는 겹쳐도 안되고 경계밖으로 나가면 안됨, 또 칸의 경계와 일치해야함, 0에도 있음 안됨
 *
 *  1을 만나면 몇칸짜리로 덮을껀지 결정해야함
 *  100 ^ 5
 *
 *  삽질회고자
 *  1. 채워주는 부분이랑, 채워줄 수 있는지 판단하는 로직을 따로 가져가자
 *  채워주다가 중간에 멈추면 다시 채워주는게 어려움
 *
 *  2. 전부 1이 들어왔을 때를 생각하
 *
 */


int field[10][10];
int origin[10][10];
int init[10][10];
int visit[10][10];
int dr[2] = {1,0};
int dc[2] = {0,1};
struct point {
    int row, col;
};
int ans = INF;
int paper_cnt[] = {5,5,5,5,5,5};

void Display(){
    cout << "============" << endl;

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 9; ++j) {
            if(field[i][j] == 0)
                cout << field[i][j]  << " ";
            else
                cout << field[i][j]  -1 << " ";
        }
        cout << endl;
    }
}

bool isIn(int row, int col){
    return row>=0 and row < 10 and col < 10 and col >= 0;
}


int coverPaper(int row, int col, int paper_size){

    int rst = 0;

    for (int i = row; i < row+paper_size; ++i) {
        for (int j = col; j < col+paper_size; ++j) {
            if(!isIn(i,j))
                return rst;
            if(field[i][j] != 1)
                return rst;
            origin[i][j] = field[i][j];
            field[i][j] = 1 + paper_size;
            rst++;
        }
    }

    return rst;
}

void recover(int row, int col, int paper_size, int change_cnt){

    for (int i = row; i < row+paper_size; ++i) {
        for (int j = col; j < col+paper_size; ++j) {
            if(change_cnt == 0)
                return;
            if(!isIn(i,j))
                return;
            if(field[i][j] != paper_size+1)
                return;
            field[i][j] = origin[i][j];
            change_cnt--;
        }
    }
}

int dfs(int row, int col, int cnt){ // --> 방향탐색
    // 맨끝이면 return

    if(cnt >= ans)
        return INF;

    if(row == 10){
        ans = cnt;
        return cnt;
    }


    int nr = row;
    int nc = col+1;
    int ret = INF;

    //범위 벗어나면 다음행으
    if(col == 9){
        nr +=1;
        nc = 0;
    }


    if(field[row][col] == 1){
        for (int i = 5; i > 0; --i) {// 색종이붙이
            int change_cnt = coverPaper(row,col, i);
            if(change_cnt == i*i and paper_cnt[i] != 0){
                paper_cnt[i]--;
                ret = min(ret, dfs(nr,nc,cnt+1));
                paper_cnt[i]++;
            }// 색종이붙이고

            recover(row,col,i, change_cnt);
        }
    } else{
        ret = dfs(nr, nc, cnt);
    }


    return ret;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            cin >> field[i][j];
            origin[i][j] = field[i][j];
        }
    }

    dfs(0,0,0);

    if(ans == INF)
        ans = -1;
    cout << ans << endl;


    /*
     * 0,0 부터 쭉 탐색, 1을 만나면 1~5를 다 덮어봄
     * 덮으면 visit check;
     */

}

