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

/*
 * 2146 다리 만들기 회고
 *  - 처음에 내륙에 있는 원소들도 큐에 넣으면서 진행해서 고생했음....
 *  - 큐에 넣을 때 이 녀석이 네방향 전부에서 한번만 들어가는지 체크 할꺼!
 */

#define MAX_V 987653210

int n;
int sea[101][101];
int visit[101][101];
struct point{
    int row, col;
};
int dr[4] = { -1, 1, 0, 0};
int dc[4] = { 0, 0, -1, 1};


bool isBoundary(int r, int c){
    return r >= 0 && c >= 0 && r < n && c < n;
}

int markingNumber(int marking, point start){

    if(sea[start.row][start.col] != 1)
        return marking;

    queue<point> que;
    que.push(start);
    visit[start.row][start.col] = 1;
    sea[start.row][start.col] = marking;
    int row, col;
    int nr, nc;

    while(!que.empty()){
        row = que.front().row;
        col = que.front().col;
        que.pop();

        for (int i = 0; i < 4; ++i) {
            nr = row + dr[i];
            nc = col + dc[i];
            if(!isBoundary(nr,nc)) continue;
            if(sea[nr][nc] == 0) continue;
            if(visit[nr][nc]) continue;
            que.push({nr,nc});
            sea[nr][nc] = marking;
            visit[nr][nc] = 1;
        }
    }

    return marking+1;

}

int getDistIsland(point start){
    if(sea[start.row][start.col] == 0)
        return MAX_V;

    memset(visit, 0, sizeof(visit));
    queue<point> que;
    que.push(start);
    visit[start.row][start.col] = 1;

    int marking = sea[start.row][start.col];
    int row, col;
    int nr, nc, ndepth;

    while(!que.empty()){
        row = que.front().row;
        col = que.front().col;
        que.pop();

        for (int i = 0; i < 4; ++i) {
            nr = row + dr[i];
            nc = col + dc[i];
            ndepth = visit[row][col] + 1;
            if(!isBoundary(nr,nc)) continue;
            if(visit[nr][nc]) continue;
            if(sea[nr][nc] == marking) continue;
            if(sea[nr][nc] == 0){
                que.push({nr,nc});
                visit[nr][nc] = ndepth;
            } else{
                return  ndepth;
            }
        }
    }

    return MAX_V;

}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int nextMarking = 2;
    int ans = MAX_V;

    cin >> n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> sea[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            nextMarking = markingNumber(nextMarking, {i,j});
        }
    }

//    Display();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ans = min(ans, getDistIsland({i,j}));
        }
    }


    cout << ans - 2 << "\n";


}

