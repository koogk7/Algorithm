#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>
#include <queue>
using namespace std;

/*
 * 이동할 수 있는 타입이 7개
 * 탈주범은 한시간에 터널 한칸을 갈 수 있음
 * 시간복잡도 4^250 --> 2^500 = 10.... 터질거 같은데?
 * 흠 다른 알고리즘은 생각나는 방법이 없다....\
 * 시작점을 기준으로 모양에 따라 갈 수 있는 방향으로 BFS?
 */

int map[52][52];
int visit[52][52];
int dr[4] = {-1,0,1,0};
int dc[4] = {0,1,0,-1};
struct point{
    int row, col;
};
int T,n,m, hour;
queue<point> q;

bool isBoundary(int r , int c)
{
    return r>=0 && r<n && c>=0 && c<m;
}

void init(){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            visit[i][j] = 0;
        }
    }
}
void Display()
{
    cout << "-------------------" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << visit[i][j] << " ";
        }
        cout << endl;
    }
}

bool CaseTernal(int v, int next, int dir){

    if(next == 2 && ( dir==1 || dir == 3 )) return false;
    if(next == 3 && ( dir==0 || dir == 2 )) return false;
    if(next == 4 && ( dir==0 || dir == 1 )) return false;
    if(next == 5 && ( dir==1 || dir == 2 )) return false;
    if(next == 6 && ( dir==2 || dir == 3 )) return false;
    if(next == 7 && ( dir==0 || dir == 3 )) return false;

    if(v == 1) return true;
    if(v == 2){
        if(dir == 0 || dir == 2) return true;
        else return false;
    }
    if(v == 3){
        if(dir == 1 || dir == 3) return true;
        else return false;
    }
    if(v == 4){
        if(dir == 0 || dir == 1) return true;
        else return false;
    }
    if(v == 5){
        if(dir == 1 || dir == 2) return true;
        else return false;
    }if(v == 6){
        if(dir == 2 || dir == 3) return true;
        else return false;
    }
    if(v == 7){
        if(dir == 0 || dir == 3) return true;
        else return false;
    } else
        return false;

}


int BFS()
{
    int rst = 1;
    while(!q.empty()){
        int row = q.front().row;
        int col = q.front().col;
        q.pop();
        int depth = visit[row][col];
        if(depth >= hour) continue;
        for (int i = 0; i < 4; ++i) {
            int nr = row + dr[i];
            int nc = col + dc[i];
            if(!isBoundary(nr,nc)) continue;
            if(visit[nr][nc]) continue;
            if(map[nr][nc] == 0) continue;
            if(!CaseTernal(map[row][col],map[nr][nc],i)) continue;
            visit[nr][nc] = depth +1;
            q.push({nr,nc});
            rst++;
        }
    }
    return rst;
}



int main(){
    point start;

    cin >> T;

    for (int t = 0; t < T; ++t) {
        int ans = 0;
        cin >> n >> m >> start.row >> start.col >> hour;

        q.push(start);
        visit[start.row][start.col] = 1;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> map[i][j];
            }
        }

        cout << "#" << t+1 << " " << BFS() << endl;
//        Display();
        init();
    }

}
