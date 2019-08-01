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
 * 1261번 알고스팟
 *  - 방향까지 고려한 3차원 DP + DFS로 접근했으나 왜 틀렸는지 모르겠다....
 *  - 나는 dp[i][j]를 , i,j 위치에서 n-1, m-1까지 도달하면서 부순 최소 벽수를 저장함
 *  - 다른 사람은 dp[i][j]를 0,0에서 부터 현재까지 최소로 부서서 오는 벽수를 저장했더
 *  - ㅅㅂ 방향으로 고려하면 안되네... 같이 겹치는 애가 무조건 나오네
 *  - DP값을 정할 때, 잘 생각을 하자1
 *
 *  우선순위 큐를 이용함
 *      각 깬 벽을 기준으로 오름차순 정렬하는 우선순위 큐를 사용
 *      이렇게 하면, 깬 벽수가 적은 녀석들부터 튀어나옴으로, 벽이 적은 녀석들로 경로를 먼저 잡게됨
 * */
#define MAX_N 101

int n,m;
int maze[MAX_N][MAX_N];
int visit[MAX_N][MAX_N];
int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
struct point{
    int row, col, break_wall;
};

struct cmp {
    bool operator()(point a, point b){
        return a.break_wall > b.break_wall;
    }
};

bool isBoundary(int r, int c){
    return r >= 0 && r < n && c >=0 && c < m;
}

int BFS(){
    priority_queue<point, vector<point>, cmp> pq;

    pq.push({0,0,0});
    visit[0][0] = 1;
    int row, col, break_wall;

    while(!pq.empty()){
        row = pq.top().row;
        col = pq.top().col;
        break_wall = pq.top().break_wall;
        pq.pop();

        if(row == n-1 and col == m-1) return break_wall;

        for (int i = 0; i < 4; ++i) {
            int nr = row + dr[i];
            int nc = col + dc[i];
            if(!isBoundary(nr,nc)) continue;
            if(visit[nr][nc]) continue;
            if(maze[nr][nc])
                pq.push({nr,nc,break_wall+1});
            else
                pq.push({nr,nc,break_wall});
            visit[nr][nc] = 1;
        }
    }

    return -1;

}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> m >> n;
    char buf;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> buf;
            maze[i][j] = buf -'0';
        }
    }

    cout << BFS()<< "\n";


}

