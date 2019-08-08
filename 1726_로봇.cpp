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


/*
 * 1726 로봇 - 회고, 2시간
 *  1. 모듈 테스트를 진행 할 때, 잘 못된 데이터를 넣어줌으로서 계속 시간을 뺏기고 있었다.
 *  2. 구조체에서 값을 직접 꺼내기보다는, 변수에 값을 담아서 사용하는 것이 가독성이 좋다.
 *  3. 처음 방향 맵핑 할 때, 다르게 맵핑하고 있었다.!
 */

using namespace std;

#define INF 987654321

int n, m;
int factory[101][101];
struct robot{
    int row, col, dir, cnt;
};
struct cmp{
    bool operator()(robot A, robot B){
        return A.cnt > B.cnt;
    }
};

robot start, dest;
int dr[] = {-1,0,1,0};
int dc[] = {0,1,0,-1};
int dist[101][101][4];
priority_queue<robot, vector<robot>, cmp> pq;

bool isBoundary(int r, int c){
    return r >= 0 && r < n && c >= 0 && c < m;
}

bool isDest(robot a){
    return a.row == dest.row && a.col == dest.col && a.dir == dest.dir;
}

void dirMap(robot& a){
    if(a.dir == 1)
        a.dir = 1;
    else if(a.dir == 2)
        a.dir = 3;
    else if(a.dir == 3)
        a.dir = 2;
    else
        a.dir = 0;
}


int turn(int mode, int origin) // mode 1 : right, 2 : left
{
    if(mode == 1)
        return (origin+1) % 4;
    else
        return (origin+3) % 4;
}

int Dijkstra(){
    pq.push(start);
    dist[start.row][start.col][start.dir] = 0;
    robot current;

    while(!pq.empty()){
        current = pq.top();
        pq.pop();
        int row = current.row;
        int col = current.col;
        int cnt = current.cnt;
        int dir = current.dir;
        int cost = dist[current.row][current.col][dir] + 1;

        if(isDest(current)) {
            return current.cnt;
        }


        for (int i = 1; i < 4; ++i) {
            int nr = row + dr[dir]*i;
            int nc = col + dc[dir]*i;
            if(!isBoundary(nr,nc)) continue;
            if(factory[nr][nc]) break;
            if(cost < dist[nr][nc][dir]){
                dist[nr][nc][dir] = cost;
                pq.push({nr, nc ,dir ,cost});
            }
        }

        robot rightRolate = {row, col, turn(1, dir), current.cnt+1};
        robot leftRolate = {row, col, turn(0, dir), current.cnt+1};

        if(cost < dist[row][col][rightRolate.dir]) {
            dist[row][col][rightRolate.dir] = cost;
            pq.push(rightRolate);
        }

        if(cost < dist[row][col][leftRolate.dir]) {
            dist[row][col][leftRolate.dir] = cost;
            pq.push(leftRolate);
        }

    }

    return -1;
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> factory[i][j];
            for (int k = 0; k < 4; ++k) {
                dist[i][j][k] = INF;
            }

        }
    }
    cin >> start.row >> start.col >> start.dir;
    cin >> dest.row >> dest.col >> dest.dir;
    start.row--; start.col--; dest.row--; dest.col--;
    dirMap(start);
    dirMap(dest);

    cout << Dijkstra() << "\n";
}

