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

/*
 * 7562 나이트의 이동
 *
 */

int T;
int n;
int board[301][301];
int visit[301][301];
struct Knight{
    int row ,col;
};
Knight start;
Knight dest;
int dr[] = {-1, -1, -2, -2,  1,  1,  2,  2};
int dc[] = {-2,  2, -1,  1, -2,  2, -1,  1};


bool isBoundary(int row, int col){
    return row >=0 and row < n and col >= 0 and col < n;
}

int BFS(Knight init){
    queue<Knight> que;

    int row, col;
    int dist = 0;

    que.push(init);
    visit[init.row][init.col] = 1;

    while(!que.empty()){
        row = que.front().row;
        col = que.front().col;
        dist = visit[row][col];
        que.pop();

        if(row == dest.row and col == dest.col){
            return dist;
        }

        for (int i = 0; i < 8; ++i) {
            int nr = row + dr[i];
            int nc = col + dc[i];

            if(!isBoundary(nr,nc)) continue;
            if(visit[nr][nc]) continue;
            que.push({nr,nc});
            visit[nr][nc] = dist + 1;
        }

    }

}


int main(){
    cin >> T;

    while(T--){
        cin >> n;
        cin >> start.row >> start.col;
        cin >> dest.row >> dest.col;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                visit[i][j] = 0;
            }
        }

        cout << BFS(start) - 1 << "\n";
    }

}

