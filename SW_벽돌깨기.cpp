#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
/*
 * 0은 빈공간
 * 구슬은 좌우로만 움직일 수 있다
 * 맨 위에 있는 벽돌만 깨뜨릴 수 있다
 * 벽돌은 1~9로 표현, 구슬이 명중한 벽둘은 상하좌우로 벽돌에 적힌 수 -1 만큼 같이 제거
 * 빈 공간이 있을 경우 벽돌은 밑으로 떨어짐
 * n개의 벽돌을 떨어뜨려 가장 많은 벽돌을 제거
 *
 * 1. BFS로 연쇄폭발 구현
 * 2. MOVE!
 * 3. DFS로 구슬을 놓을 column 선택, 완전탐색!
 *
 *
 * 풀이중 했던 실수
 * 1. Print 함수를 따로 만들어서, 디버깅에 사용하자!
 * 2. 항상 배열의 범위를 체크하자!, 사소한거라도 범위를 넘어가는 녀석이 없도록 바운더리 체크 확실히!
 * 3. 뭐가 문제인지 모를 때는 하나하나 다 콘솔에 찍어보자!
 * 4. 방문체크를 했다면, 반드시 방문해제를 해주자!
 * 5. 시물레이션의 대부분은 원본을 저장하고 시작하는 것이 좋다.
 * 6. 초기화 철저히!
 * * */


using namespace std;

struct point{
    int row ,col;
};

int t;
int n,w,h;
int box[17][14];
int original[17][14];
int visit[17][14];
int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};
queue<point> que; // 깨질 벽돌들을 넣는다.
int ans = 1000000;
int remain;

int sel[10]; // 왜 10이상만 되지?
int col_visit[14];

int cnt = 0;

bool isBoundary(int r, int c)
{
    return r>=0 && r<h && c>=0 && c<w;
}

void InitVisit()
{
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            visit[i][j] = 0;
        }
    }
}

void Print()
{
    cout << "------------------" <<endl;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            cout <<  box[i][j] << " ";
        }
        cout << endl;
    }
}


void Move()
{
    for (int i = h-2; i >= 0; --i) {
        for (int j = 0; j < w; ++j) {
            if(box[i][j] == 0) continue;
            if(box[i+1][j] != 0) continue;
            int move_cnt = i+1;
            while(box[move_cnt][j] == 0 && move_cnt <h)
            {
                box[move_cnt][j] = box[move_cnt-1][j];
                box[move_cnt-1][j] = 0;
                move_cnt++;
            }
        }
    }
}

void BFS() // 연쇄폭발
{
    int nr, nc;
    int row, col;
    int count = 0;
    while(!que.empty())
    {
        row = que.front().row;
        col = que.front().col;
        que.pop();
        count = 1;
        box[row][col]--;
        while(box[row][col]) {
            box[row][col]--;
            for (int k = 0; k < 4; ++k) {
                dr[k] = dr[k] * count;
                dc[k] = dc[k] * count;
            }
            for (int i = 0; i < 4; ++i) {
                nr = row + dr[i];
                nc = col + dc[i];
                if(!isBoundary(nr,nc)) continue;
                if(box[nr][nc] == 0) continue;
                if(visit[nr][nc] == 1 ) continue;
                visit[nr][nc] = 1;
                que.push({nr,nc});
            }
            for (int k = 0; k < 4; ++k) {
                if(dr[k])
                    dr[k] = dr[k] / count;
                if(dc[k])
                    dc[k] = dc[k] / count;
            }
            count++;
        }
    }
}

void DFS(int depth)
{
    if(depth == n){
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < h; ++k) {
                if(box[k][sel[i]]){
                    que.push({k,sel[i]});
                    BFS();
                    Move();
                    InitVisit();
                    break;
                }
            }
        }
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if(box[i][j] != 0)
                    remain++;
                box[i][j] = original[i][j];
            }
        }
        ans = remain < ans ? remain : ans;
        remain = 0;
        return;
    }

    for (int k = 0; k < w; ++k) {
        sel[depth] = k;
        DFS(depth+1);
    }

    return;

}



int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    int cnt = 1;
    cin >> t;
    while(t--)
    {
        cin >> n >> w >> h;

        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                cin >> box[i][j];
                original[i][j] = box[i][j];
            }
        }

        DFS(0);
        cout <<"#" <<cnt++ << " " <<ans <<'\n';
        ans = 100000;
    }


}

