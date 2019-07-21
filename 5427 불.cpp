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
 * 5427 불
 * - que에 들어간 좌표가 불인지, 상근인지 확인하는 변수가 필요하다 --> isFire
 * - 문제에서 불이 붙을려는 칸으로 이동 할 수 없음으로, 상근이는 가장 마지막에 큐에 넣어준다.
 * */



int t, w,h;
char building[1001][1001]; // . : 빈공간, # : 벽, * : 불, @ : 상근이 시작위치
int visit[1001][1001];
struct point{
    int row, col;
    bool isFire;
};
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

bool isBoundary(int r, int c){
    return r >= 0 && r < h && c >=0 && c < w;
}

int BFS(queue<point> &que){
    int row, col;
    bool isFire;
    int nr, nc, ndist;

    while(!que.empty()){
        row = que.front().row;
        col = que.front().col;
        isFire = que.front().isFire;
        que.pop();
        ndist = visit[row][col] + 1;

        for (int i = 0; i < 4; ++i) {
            nr = row + dr[i];
            nc = col + dc[i];
            if(!isBoundary(nr,nc)){
                if(!isFire) return ndist-1;
                continue;
            }
            if(visit[nr][nc]) continue;
            if(building[nr][nc] == '#') continue;
            visit[nr][nc] = ndist;
            que.push({nr,nc, isFire});
        }
    }

    return -1;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> t;

    while(t--){
        queue<point> que;
        int ans;
        cin >> w >> h;
        point start;

        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                cin >> building[i][j];
                if(building[i][j] == '*') {
                    que.push({i, j, true});
                    visit[i][j] = 1;
                 } else if(building[i][j] == '@'){
                    start = {i,j,false};
                    visit[i][j] = 1;
                } else{
                    visit[i][j] = 0;
                }
            }
        }
        que.push(start);
        ans = BFS(que);
        if(ans == -1) cout << "IMPOSSIBLE" << "\n";
        else cout << ans << "\n";
    }


}

