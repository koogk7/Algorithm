#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

/*
 *  1번 한쪽방향
 *  2번 서로 반대되는 두방향
 *  3번 직각방향
 *  4번 세방향
 *  5번 네방향
 *
 *  cctv는 감시할 수 있는 방향에 있는 칸 전체를 감시할 수 있다.
 *  단 벽은 통과할 수 없다.
 *  cctv는 회전 시킬 수 있는데, 회전은 항상 90도 방향으로, 감시하려고 하는 방향이 가로 또는 세로
 *  cctv는 cctv를 통과 할 수 있다.
 *
 *  cctv의 방향을 적절히 정해서, 사각 지대의 최소 크기를 구해라
 *  cctv의 최대개수는 8개를 넘지않는다.
 *  접근방법
 *      우선 5번은 방향을 정할 필요가 없어. 5번을 가장먼저 마킹
 *      cctv의 갯수가 최대 8개...완전탐색?
 *      cctv위치는 정해져 있고, 방향만 선택하면되네 그럼 최악의 경우의 수는
 *      4^8 ---> 2^16 = 1024 * 32 충분
 *
 *   1. 벡터에 cctv 위치를 넣는다.
 *   2. map 값으로 정렬 , log n
 *   3. 0부터 4방향으로 백트레킹 시작
 *      Backtracking(point a, int cnt, int dir, int idx)
 *      탈출조건
 *          map[i][j] = 6, 범위초과, 인덱스초과
 *      index에 도달했을 때
 *
   6 6
    1 0 0 0 0 0
    0 1 0 0 0 0
    0 0 1 0 0 0
    0 0 0 1 0 0
    0 0 0 0 1 0
    0 0 0 0 0 1

 */

int n,m;
int map[10][10];
int cover[10][10];
struct point{
    int row, col;
};
vector<point> v;
vector<int> test;
int dr[4] = {-1,0,1,0};
int dc[4] = {0,1,0,-1};
void Display(){
//    cout << "-----------------------" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << cover[i][j] << " ";
        }
        cout << endl;
    }
}

bool isBoudary(int r, int c)
{
    return r>=0 && r<n && c>=0 && c<m;
}

int FillCover(point a, int dir, int flag){
    int rst = 0;
    while(1){
        a.row += dr[dir];
        a.col += dc[dir];
        if(!isBoudary(a.row, a.col)) break;
        if(map[a.row][a.col] == 6) break;
        if(cover[a.row][a.col] != flag) {
            cover[a.row][a.col] = flag;
            if(map[a.row][a.col] == 0)
                rst++;
        }
    }
    return rst;
}

int DrawCover(point a, int dir, int flag){
    int shape = map[a.row][a.col];
    int rst = 0;
    if(shape == 1){
        rst += FillCover(a,dir,flag);
    }
    if(shape == 2){
        rst +=FillCover(a,dir,flag);//dir 방향으로 fill
        rst +=FillCover(a,(dir+2)%4,flag);//(dir+2)%4 방향으로 fill
    }
    if(shape == 3){
        rst +=FillCover(a,dir,flag);
        rst +=FillCover(a,(dir+1)%4,flag);
    }
    if(shape == 4){
        rst +=FillCover(a,dir,flag);
        rst +=FillCover(a,(dir+1)%4,flag);
        rst +=FillCover(a,(dir+3)%4,flag);
    }
    if(shape == 5){
        rst +=FillCover(a,dir,flag);
        rst +=FillCover(a,(dir+1)%4,flag);
        rst +=FillCover(a,(dir+2)%4,flag);
        rst +=FillCover(a,(dir+3)%4,flag);
    }

    return rst;

}

int BackTracking(int cnt, int idx)
{
    if(idx == v.size()) {

        for (int k = 0; k < test.size(); ++k) {
            DrawCover(v[k],test[k],1);
            cover[v[k].row][v[k].col] = 1;
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if(map[i][j] == 0){
                    if(cover[i][j] == 0)
                        cnt++;
                }
            }
        }

        for (int k = 0; k < test.size(); ++k) {
            DrawCover(v[k],test[k],0);
        }
        return cnt;
    }
    int ret = 10000000;

    for (int i = 0; i < 4; ++i) {
        test.push_back(i);
        ret = min(ret,BackTracking(cnt,idx+1));
        cover[v[idx].row][v[idx].col] = 0;
        test.pop_back();
    }

    return ret;

}

int main(){
    cin >> n;
    cin >> m;
    int ans = n*m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> map[i][j];
            if(map[i][j] != 0){
                if(map[i][j] != 6){
                    v.push_back({i,j});
                    cover[i][j] = 1;
                }
            }
        }
    }

    cout << BackTracking(0,0) << endl;

}