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
 * 16985 Maaaaaaze
 *  - 구현해야 될 부분이 매우 많아 기능단위로 테스트하면서 진행해야한다.
 *  - 실수를 할 수 있는 부분이 굉장히 많다.
 *  - 이 코드는 내가 짠 코드가 아니라 다른 사람의 코드를 참고했다
 *  - 비트연산에 대해 공부를 좀 해야겠다
 */

#define MAX_N 123456789
// board[dir][i][j][k] : i번째 판을 dir번 돌렸을 때
int board[4][5][5][5];
int maze[5][5][5];
int visit[5][5][5];
int dr[6] = {-1, 1, 0, 0, 0, 0};
int dc[6] = {0, 0, -1, 1, 0, 0};
int dn[6] = {0, 0, 0, 0, -1, 1};
struct point {
    int num, row, col;
};

void initVisit(){
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            for (int k = 0; k < 5; ++k) {
                visit[i][j][k] = 0;
            }
        }
    }
}

bool isBoundary(int r, int c, int d){
    return r >= 0 && r < 5 && c >= 0 && c < 5 && d >= 0 && d < 5;
}

void turnFrame(int frameNum){
    int iter = 1;

    while(iter != 4) {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                board[iter][frameNum][i][j] = board[iter-1][frameNum][4-j][i];
            }
        }
        iter++;
    }
}


int BFS(){
    if(maze[0][0][0] == 0 or maze[4][4][4] == 0)
        return MAX_N;

    initVisit();

    int num, row, col;
    int nd, nr, nc;
    int nextDist;
    queue<point> que;
    que.push({0, 0, 0});
    visit[0][0][0] = 1;

    while(!que.empty()){
        num = que.front().num;
        row = que.front().row;
        col = que.front().col;
        que.pop();
        nextDist = visit[num][row][col] + 1;

        for (int i = 0; i < 6; ++i) {
            nd = num + dn[i];
            nr = row + dr[i];
            nc = col + dc[i];
            if(!isBoundary(nr,nc,nd)) continue;
            if(maze[nd][nr][nc] == 0) continue;
            if(nd == 4 and nr == 4 and nc == 4)
                return nextDist - 1;
            if(visit[nd][nr][nc]) continue;
            que.push({nd,nr,nc});
            visit[nd][nr][nc] = nextDist;
        }
    }

    return MAX_N;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) { // 입력
            for (int k = 0; k < 5; ++k) {
                cin >> board[0][i][j][k];
            }
        }
        turnFrame(i); // 판 회전 모습들을 미리 저장

    }


    int order[] = {0,1,2,3,4};
    int ans = MAX_N;

    do{
        for (int tmp = 0; tmp < 1024; ++tmp) {
            int brute = tmp; // 5개의 판에 대해 dir을 정해주기 위한 변수
            for (int i = 0; i < 5; ++i) { // 판번호
                int dir = brute % 4;
                brute /= 4;
                for (int j = 0; j < 5; ++j) { // row 번호
                    for (int k = 0; k < 5; ++k) {// col 번호
                        maze[i][j][k] = board[dir][order[i]][j][k];
                    }
                }
            }
            ans = min(ans, BFS());
        }
    }while(next_permutation(order,order+5));


    if(ans == MAX_N) ans = -1;

    cout << ans;

}

