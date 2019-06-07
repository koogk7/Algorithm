#include <stdio.h>
#include <iostream>
#include <vector>

/*
 * 서로 겹치면 안된다
 * 모두 연결되어 있어야 한다.
 * 꼭짓점끼리 연결되어야 한다
 * 테트로미노 안에 합이 최대가 되야해!
 * */



using namespace std;

int n,m;
int box[502][502];
int visit[502][502];
int ans;

struct point
{
    int row, col;
};

vector<point> path;


int d_row[] = {-1,1,0,0};
int d_col[] = {0,0,-1,1};

bool isBoundary(int r, int c)
{
    int isRow = r>=0 && r< n;
    int isCol = c>=0 && c<m;

    return isRow && isCol;
}

void dfs(int r,int c, int sum, int depth)
{
    if(depth == 4){
        if(ans < sum){
            ans = sum;
        }
        return;
    }

    int nr, nc, ex_check = 0;
    visit[r][c] = true;

//    path.push_back({r,c});
//    if(path.size() == 3){
//        for (int i = 0; i < 4; ++i) {
//            nr = path[1].row +d_row[i];
//            nc = path[1].col+ d_col[i];
//            if(!isBoundary(nr,nc)) continue;
//            if(!visit[nr][nc] && ex_check < box[nr][nc]){
//                ex_check = box[nr][nc];
//            }
//        }
//        ex_check += sum;
//        ans = ans<ex_check ? ex_check : ans;
//    }


    for (int i = 0; i < 4; ++i) {
        nr = r + d_row[i];
        nc = c+ d_col[i];
        if(!isBoundary(nr,nc)) continue;
        if(!visit[nr][nc]){
            dfs(nr,nc,sum+box[r][c],depth+1);
        }
    }

    visit[r][c] = false;
//    path.pop_back();

}


void no_dfs(int r, int c)
{
    int nr, nc, sum = box[r][c];
    int min = 1000000;
    for (int i = 0; i < 4; ++i) {
        nr = r + d_row[i];
        nc = c + d_col[i];
        if(!isBoundary(nr,nc)) {
            min = 0;
            continue;
        }
        sum += box[nr][nc];
        min = min < box[nr][nc] ? min : box[nr][nc];
    }
    sum -= min;
    ans = ans > sum ? ans : sum;
}

int main(){

    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> box[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            dfs(i,j,0,0);
            no_dfs(i,j);
        }
    }

    cout << ans <<endl;

}

