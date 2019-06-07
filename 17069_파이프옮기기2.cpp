#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <stack>
#include <string.h>

typedef long long ll;
using namespace std;
/*
 * 가로나 세로는 한칸만 보면되고, 대각선일 때는 아래,왼쪽,왼쪽아래 확인하면 되네
 */

int n;
int map[33][33];
ll dp[33][33][3];
int dr[] = {1,0,1};
int dc[] = {0,1,1};

bool isBoundary(int row, int col){
    return row>=0 && row<n && col>=0 && col<n;
}

bool isGo(int row, int col, int dir){
    if(dir != 2){
        if(!isBoundary(row,col)) return false;
        if(map[row+dr[dir]][col+dc[dir]] == 1) return false;
        else return true;
    }
    else{
        for (int i = 0; i < 3; ++i) {
            int nr = row + dr[i];
            int nc = col + dc[i];
            if(!isBoundary(nr,nc))return false;
            if(map[nr][nc] == 1) return false;
        }
        return true;
    }
}

ll DFS(int row, int col, int dir){
    if(row == n-1 && col == n-1){
        return 1;
    }
    if(dp[row][col][dir] != -1) return dp[row][col][dir];
    dp[row][col][dir] = 0;

    if(dir != 2){
        if(isGo(row,col,dir)){
            int nr = row + dr[dir];
            int nc = col + dc[dir];
            dp[row][col][dir] += DFS(nr,nc,dir);
        }
        if(isGo(row,col,2)){
            int nr = row+ dr[2];
            int nc = col+ dc[2];
            dp[row][col][dir] += DFS(nr,nc,2);
        }
    }
    else{
        for (int i = 0; i < 3; ++i) {
            int nr = row + dr[i];
            int nc = col + dc[i];
            if(!isGo(row,col,i)) continue;
            dp[row][col][dir] += DFS(nr,nc,i);
        }
    }
    return dp[row][col][dir];
}

int main(){
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> map[i][j];
        }
    }
    memset(dp,-1,sizeof(dp));
    cout << DFS(0,1,1) <<endl;
}
