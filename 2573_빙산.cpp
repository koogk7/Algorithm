#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>

/*
 * 동서남북 네방향으로 붙어 있는 0의 칸의 개수만큼 줄어듬
 * --->
 * 한 덩어리의 빙산이 주어질 때 두 덩어리 이상으로 분리되는 최초의 시간을 구해라
 * 한번의 탐색마다 네방향으로 0을 체크, 빙하크기 재조정, 구역체크
 * 구역 체크는 어떻게? dfs 탐색 --> 두번 이상의 dfs 탐색이 진행 될 시 종료!
 *
 * */
using namespace std;

int N,M;
int box[302][302];
int melting_box[302][302];
int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};
int ans;// 시간
int visit[302][302];
int segment = 1;

struct point{
    int row, col;
};


void Melting(int row, int col)
{
    if(box[row][col] == 0 )return;
    int nr,nc;
    for (int i = 0; i < 4; ++i) {
        nr = row+ dr[i];
        nc = col+ dc[i];
        if(box[nr][nc] == 0)
            melting_box[row][col]--;
    }
    if(melting_box[row][col] < 0 )
        melting_box[row][col] = 0;
}

void dfs(int row, int col)
{
    if(box[row][col] == 0) return;

    int nr,nc;

    for (int i = 0; i < 4; ++i) {
        nr = row+ dr[i];
        nc = col+ dc[i];
        if(box[nr][nc] != 0 && !visit[nr][nc]) {
            visit[nr][nc] = 1;
            dfs(nr, nc);
        }
    }
}

void sync()
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            box[i][j] = melting_box[i][j];
            visit[i][j] = 0;
        }
    }
}


int main()
{
    int first_flag =1;
    int start_r, start_c;
    int iter_dfs = 0;
    cin >> N >> M;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> box[i][j];
            melting_box[i][j] = box[i][j];
            if(first_flag && box[i][j])
            {
                start_r = i;
                start_c = j;
                first_flag = 0;
            }
        }
    }

    while(segment == 1){

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                Melting(i,j);
            }
        }

        sync();

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if(visit[i][j] == 0 && box[i][j] != 0)
                {
                   dfs(i,j);
                   iter_dfs++;
                }
            }
        }

        if(iter_dfs > 1) break;
        if(iter_dfs == 0){
            ans = -1;
            break;
        }
        iter_dfs = 0;
        ans++;
    }

    cout << ans+1 <<endl;


}