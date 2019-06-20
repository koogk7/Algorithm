#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <stack>
#include <string.h>
#include <queue>
#include <set>
using namespace std;

/*
 * 방향을 위에서부터 아래로 향하면, 겹치는 부분이 없다!
 * 1. 0이면 pass, 1이면 해당 구역크기를 구한다. 구역크기 구하는 것은 어떻게?
 *  ---->
 * 회고
 *  fill 채우는 부분에서 삽질 계속하고 있었음, 범위 n으로 값을 채우고 있었다
 *  마지막 끝 부분 도달했을 때를 놓쳤음
 *  역시 처음에 생각을 다 하고 접근!, 디버깅 기능을 적극활용하자!
 *
 */
#define MA 10000000
int map[12][12];
int orgin[12][12];
vector<int> remain;
int ans = MA;

bool isBoundary(int r, int c)
{
    return r>=0 && r<10 && c>=0 && c<10;
}

bool isCover(int row, int col, int n){

    for (int i = row; i <= row + n; ++i) {
        for (int j = col; j <= col + n; ++j) {
            if(!isBoundary(i,j)) return false;
            if(map[i][j] != 1) return false;
        }
    }
    return true;
}

void Fill(int row, int col, int n, int value)
{
    for (int i = row; i <= row + n; ++i) {
        for (int j = col; j <= col + n; ++j) {
            map[i][j] = value;
        }
    }
}


int BackTracking(int row, int col, vector<int>rema, int cnt)
{
    if(row == 3 && col == 6)
    if(cnt >= ans) return MA;

    int ret = MA;
    if(row == 9 && col == 9){
        if(map[row][col] == 1){
            if(rema[0] == 0)
                return MA;
            else
                return cnt+1;
        }
        ans = cnt;
        return cnt;
    }
    if(map[row][col] != 1){
        if(col != 9)
            ret = BackTracking(row,col+1,rema,cnt);
        else
            ret = BackTracking(row+1,0,rema,cnt);
        return ret;
    }

    for (int i = 0; i < 5; ++i) {
        if(rema[i] == 0) continue;
        if(!isCover(row,col,i)) continue;
        Fill(row,col,i,i+2);
        rema[i]--;
        int nc = col+i;
        if(isBoundary(row,nc+1)) ret = min(ret,BackTracking(row,nc+1,rema,cnt+1));
        else ret = min(ret,BackTracking(row+1,0,rema,cnt+1));
        Fill(row,col,i,1);
        rema[i]++;
    }

    return ret;

}



int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    remain = vector<int>(5,5);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            cin >> map[i][j];
            orgin[i][j] = map[i][j];
        }
    }
    int temp = BackTracking(0,0,remain,0);
    if(temp == MA) cout << -1 <<endl;
    else cout << temp << endl;

}
