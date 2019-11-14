// ConsoleApplication2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <stack>
#include <map>
#include <set>

using namespace std;

typedef long long ll;

/* 1600 말이 되고픈 원숭이
 * - W*H = 200 * 200 = 4 * 10^4
 * - K = 30
 * - 하나의 지점에서 액션은 다음과 같다
 *  - 원숭이 -> 상하좌우
 *  - 말 -> 8가지
 *  - visit[말 cnt][W][H] ==> 4 * 10^4 * 30 * 12
 */

#define MAX_N 68
#define INF 987654321
int k, w, h;
struct point{
    int row, col, horseCnt;
};
int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};
int horseRow[] = {-2,-2,-1,-1,1,1,2,2};
int horseCol[] = {-1,1,-2,2,-2,2,-1,1};
int field[201][201];
int visit[31][201][201];
int ans = INF;

bool isIn(int r, int c){
    return r>=0 and r<h and c>=0 and c<w;
}

void moveMonkey(queue<point>& que, int dist){
    for (int i = 0; i < 4; ++i) { // 원숭이 이동
        int nr = que.front().row + dr[i];
        int nc = que.front().col + dc[i];
        int nh = que.front().horseCnt;

        if(!isIn(nr,nc))
            continue;
        if(visit[nh][nr][nc])
            continue;
        if(field[nr][nc])
            continue;
        que.push({nr,nc,nh});
        visit[nh][nr][nc] = dist + 1;
    }
}

void moveHorse(queue<point>& que, int dist){
    if(que.front().horseCnt == 0)
        return;

    for (int i = 0; i < 8; ++i) { // 말 이동
        int nr = que.front().row + horseRow[i];
        int nc = que.front().col + horseCol[i];
        int nh = que.front().horseCnt - 1;

        if(!isIn(nr,nc))
            continue;
        if(visit[nh][nr][nc])
            continue;
        if(field[nr][nc])
            continue;
        que.push({nr,nc,nh});
        visit[nh][nr][nc] = dist + 1;
    }
}

void BFS(){
    queue<point> que;
    que.push({0,0,k});
    for (int i = 0; i <= k; ++i) {
        visit[k][0][0] = 1;
    }

    while(!que.empty()){
        point queFront = que.front();
        int dist = visit[queFront.horseCnt][queFront.row][queFront.col];

        if(queFront.row == h-1 and queFront.col == w-1){
            ans = min(ans, dist);
        } else if(dist < ans){
            moveMonkey(que, dist);
            moveHorse(que, dist);
        }

        que.pop();
    }
}


int main() {
    cin >> k >> w >> h;

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            cin >> field[i][j];
        }
    }

    BFS();
    if(ans == INF)
        ans = -1;
    else
        ans -= 1;

    cout << ans;
}


