#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <stack>
#include <string.h>
#include <queue>

using namespace std;
/*
 * 8** 8 = 64 완탐 64c3이니까 충분
 * 1시간 18분 걸림, 과자먹으면서 조금 느슨하게함
 */
int n,m;
int map[10][10];
int orgin[10][10];
int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};
struct point{
    int row,col;
};
vector<point> empty_wall;
queue<point> virus;

bool isBoundary(int r, int c){
    return r>=0 && r<n && c>=0 && c<m;
}

int Spread(queue<point> q){
    int ret = empty_wall.size();
    queue<point> init;
    while(!q.empty()){
        int row = q.front().row;
        int col = q.front().col;
        init.push(q.front());
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int nr = row + dr[i];
            int nc = col + dc[i];
            if(!isBoundary(nr,nc)) continue;
            if(map[nr][nc] != 0) continue;
            map[nr][nc] = 3;
            q.push({nr,nc});
            ret--;
        }
    }

    while(!init.empty()){
       int row = init.front().row;
       int col = init.front().col;
       init.pop();
       if(map[row][col] == 2) continue;
       map[row][col] = 0;
   }
    return ret;
}

int PutWall(int index, int cnt){
    if(cnt == 3){
        int ret = Spread(virus); //바이러스 퍼뜨리고 안전영역 구함
        return ret;
    }

    int ret = -1;

    for (int i = index+1; i < empty_wall.size(); ++i) {
        point item = empty_wall[i];
        if(map[item.row][item.col] != 0) continue;
        map[item.row][item.col] = 1;
        ret = max(ret,PutWall(i,cnt+1));
        map[item.row][item.col] = 0;
    }

    return ret;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> map[i][j];
            orgin[i][j] = map[i][j];
            if(map[i][j] == 0) empty_wall.push_back({i,j});
            if(map[i][j] == 2) virus.push({i,j});
        }
    }
    cout << PutWall(-1,0) - 3 << endl;
}
