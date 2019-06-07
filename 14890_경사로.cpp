#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
/*
 *
 * 경사로를 놓기 위한 조건
 *  1. 경사로를 놓기 위한 칸의 높이가 모두 같아야한다.
 *  2. 경사로는 낮은 칸에 놓인다.
 *  3. 경사로를 놓는 칸은 연속되어 있어야 한다.
 *  4. 경사로를 놓은 곳에는 경사로를 놓을 수 없다.
 *
 * 검사는 row 방향으로 한번하고, col 방향으로 한번하자
 * 그리고 다 초기한 후에 col 방향 먼저, row 방향 먼저 체크
 * 경사로을 놓은 좌표는 어떻게 표시할꺼야? visit
 * 경사로의 놓기 위한 사이즈 체크는 어떻게?
 * queue? ㄴㄴ, 양방향 탐색!
 *
 * * */

using namespace std;

struct point{
    int row, col;
};

int n,l;
int box[102][102];
int rvisit[102][102]; // 경사로 표시
int cvisit[102][102]; // 경사로 표시
int size; // 경사로를 놓을 수 있는지 사이즈 체크
int flag; // 0: row, 1: col
int ans;
int dir[] = {-1,1};

bool isBoundary(int r, int c)
{
    return r>=0 && r<n && c>=0 && c<n;
}

void Print()
{
    cout << "---------Col-----------------" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout<< cvisit[i][j] << " ";
        }
        cout << endl;
    }
    cout << "---------Row-----------------" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout<< rvisit[i][j] << " ";
        }
        cout << endl;
    }
}

bool isPut(point a, point b)
{

    // 높이가 낮은 지점을 선정합니다. a이면 후방 검사를, b이면 전방검사를 실시합니다.
    point lower = box[a.row][a.col] < box[b.row][b.col] ? a : b;
    int dir_flag = box[a.row][a.col] < box[b.row][b.col] ? 0 : 1;
//    cout <<"row : " << lower.row << " col : " << lower.col << " dir : " <<dir_flag << endl;
    //상하 또는 좌우로 경사로 사이즈만큼 탐색합니다.
    int bottom = 0;
    int nrow, ncol; // 다음 탐색 지점을 저장할 변수입니다.
    while(bottom < l)
    {
        if(flag == 0) // 좌우탐색
        {
            if(dir_flag == 0) ncol = lower.col - bottom; // 후방검사
            if(dir_flag == 1) ncol = lower.col + bottom; // 전방검사
            if(!isBoundary(lower.row,ncol)) break; // 범위를 벗어나면 탈출
            if(cvisit[lower.row][ncol] == 1) break; // 경사로가 있다면 탈출
            if(box[lower.row][lower.col] != box[lower.row][ncol])break; // 평평하지 않다면 탈출
        }
        if(flag == 1) //상하탐색
        {
            if(dir_flag == 0) nrow = lower.row - bottom; // 후방검사
            if(dir_flag == 1) nrow = lower.row + bottom; // 전방검사
            if(!isBoundary(nrow,lower.col)) break; // 범위를 벗어나면 탈출
            if(rvisit[nrow][lower.col] == 1) break; // 경사로가 있다면 탈출
            if(box[lower.row][lower.col] != box[nrow][lower.col])break; // 평평하지 않다면 탈출
        }
        bottom++;
    }
    if(bottom != l) return false;
//    cout << "bottom : " << bottom <<endl;
    bottom = 0;
    while(bottom<l) // 경사로를 놓습니다.
    {
        if(flag == 0) // 좌우탐색
        {
            if(dir_flag == 0) ncol = lower.col - bottom;
            if(dir_flag == 1) ncol = lower.col + bottom;
            cvisit[lower.row][ncol] = 1;
        }
        if(flag == 1) // 상하탐색
        {
            if(dir_flag == 0) nrow = lower.row - bottom;
            if(dir_flag == 1) nrow = lower.row + bottom;
            rvisit[nrow][lower.col] = 1;
        }
        bottom++;
    }
    return true;
}

void InitVisit(point a, int flag)
{
    if(flag == 0)
    {
        for (int i = 0; i < n; ++i) {
            cvisit[a.row][i] = 0;
        }
    }
    if(flag == 1)
    {
        for (int i = 0; i < n; ++i) {
            rvisit[i][a.col] = 0;
        }
    }

}

int main(){

    cin >> n >> l;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> box[i][j];
        }
    }

    flag = 0; // Row 탐색

    for (int i = 0; i < n; ++i) {
        int j = 0;
        for (j = 0; j < n-1; ++j) {
            int gap = abs(box[i][j] - box[i][j+1]);
            if(gap > 1) break;
            if(gap == 0) continue;
            if(!isPut({i,j},{i,j+1}))break;
        }
        if(j == n-1) {
            ans++;
        }
        else {
            InitVisit({i,0},0);
        }
    }

    flag = 1;

    for (int i = 0; i < n; ++i) {
        int j = 0;
        for (j = 0; j < n-1; ++j) {
            int gap = abs(box[j][i] - box[j+1][i]);
            if(gap > 1) break;
            if(gap == 0) continue;
            if(!isPut({j,i},{j+1,i}))break;
        }
        if(j == n-1) {
            ans++;
        }
        else {
            InitVisit({0,i},0);
        }
    }


//    Print();
    cout << ans << endl;

}

