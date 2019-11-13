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

/*
 * 6593 상범빌딩
 * - 3차원 BFS
 *
 */

#define MAX_N 68
#define INF 123456789123

int l,r,c;
char building[31][31][31];
int visit[31][31][31];
struct point{
    int floor, row, col;
};
int df[] = {-1,1,0,0,0,0};
int dr[] = {0,0,-1,1,0,0};
int dc[] = {0,0,0,0,-1,1};
point startPoint;
point endPoint;


bool isBoundary(int f, int row, int col){
    return f >= 0 and f < l and row >= 0 and row < r and col >= 0 and col < c;
}

int BFS(){
    queue<point> que;
    que.push(startPoint);
    visit[startPoint.floor][startPoint.row][startPoint.col] = 1;

    while(!que.empty()){
        int floor = que.front().floor;
        int row = que.front().row;
        int col = que.front().col;
        int dist = visit[floor][row][col];
        que.pop();

        for (int i = 0; i < 6; ++i) {
            int nf = floor + df[i];
            int nr = row + dr[i];
            int nc = col + dc[i];

            if(!isBoundary(nf,nr,nc))
                continue;
            if(visit[nf][nr][nc])
                continue;
            if(building[nf][nr][nc] == '#')
                continue;

            if(nf == endPoint.floor and nr == endPoint.row and nc == endPoint.col)
                return dist;

            que.push({nf,nr,nc});
            visit[nf][nr][nc] = dist+1;
        }
    }

    return -1;
}


int main() {

    while(1) {

        cin >> l >> r >> c;

        if(l == 0 and r == 0 and c == 0)
            break;

        int ans = 0;

        for (int i = 0; i < l; ++i) {
            for (int j = 0; j < r; ++j) {
                for (int k = 0; k < c; ++k) {
                    cin >> building[i][j][k];
                    if (building[i][j][k] == 'S')
                        startPoint = {i, j, k};
                    if (building[i][j][k] == 'E')
                        endPoint = {i, j, k};
                }
            }
        }

        ans = BFS();
        memset(visit,0, sizeof(visit));

        if (ans == -1) {
            cout << "Trapped!" << "\n";
        } else {
            cout << "Escaped in " << ans << " minute(s)." << "\n";
        }

    }

}


