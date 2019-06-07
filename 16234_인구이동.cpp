#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
/*
 * 1. 두 나라의 인구 차이가 l~r사이라면 국경선이 열린다.
 * 2. 국경선이 열려있다면, 인구이동 시작, 연합이 된다.
 * 3. 연합을 이루고 잇는 각 칸의 인구수는 총합/갯수가 된다.
 * 4. 연합해제
 * 5. 인구이동이 가능 할 때까지 반복
 *
 * 우선 연합을 찾아야해! --> BFS로 찾아서 큐로 넣자
 * 큐에 넣을 때마다 총합 올려주고, 큐 갯수 올려주자
 *
 *
 *
 * * */


using namespace std;

struct point{
    int row, col;
};

int n, l, u;
int box[52][52];
int visit[52][52];
queue<point> que; // BFS 에 사용될 큐
queue<point> team; // 연합 큐
int total, cnt;
int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};
int ans;
int go_flag = 1;

bool isBoundary(int r, int c)
{
    return r>=0 && r< n && c>=0 && c<n;
}

bool isTeam(point a, point b)
{
    int gap = abs(box[a.row][a.col] - box[b.row][b.col]);
    return gap >= l && gap <= u;
}

void BFS()
{
    int nr, nc;
    int row , col;
    while(!que.empty())
    {
        row = que.front().row;
        col = que.front().col;
        que.pop();

        for (int i = 0; i < 4; ++i) {
            nr = row + dr[i];
            nc = col + dc[i];
            if(!isBoundary(nr,nc)) continue;
            if(!isTeam({row,col},{nr,nc})) continue;
            if(visit[nr][nc] == 1) continue;
            visit[nr][nc] = 1;
            que.push({nr,nc});
            team.push({nr,nc});
            total += box[nr][nc];
            cnt++;
        }
    }
}


void Move()
{
    if(cnt == 0) return;
    int r, c;
    int people = total / cnt;
    while(!team.empty())
    {
        r = team.front().row;
        c = team.front().col;
        team.pop();
        box[r][c] = people;
    }
    total = 0;
    cnt = 0;
    go_flag = 1;
}

void InitVisit()
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            visit[i][j] = 0;
        }
    }
}

void Print()
{
    cout << "---------------------" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << box[i][j] << " ";
        }
        cout << endl;
    }
}

int main(){

    cin >> n >> l >> u;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> box[i][j];
        }
    }


    while(go_flag)
    {
        go_flag = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if(visit[i][j] == 1) continue;
                que.push({i,j});
                BFS();
                Move();
            }
        }
        if(go_flag == 0) break;
        InitVisit();
        ans++;
    }

//    Print();
    cout << ans << endl;


}

