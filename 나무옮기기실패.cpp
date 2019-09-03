#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <stack>
#include <string.h>
#include <queue>
using namespace std;

/* 통나무의 길이는 항상 3, B의 개수와 E의 개수는 같다
 * 통나무를 움직이는 방법은 상하좌우, 회전(중심점을 중심으로 90도 회전)
 * 움직일 위치에 다른 나무가 없어야만 움직일 수 있다.
 * 움직임은 한번에 한칸씩만!
 * 회전이 가능하기 위해서는 3*3구역에 나무가 없어야해
 * 처음위치에 최종위치로 이동하는 최단경로를 구해라
 * 맵의 크기는 최대 2500
 * 
 * 중심 좌표만 저장하고 가로인지 세로인지 플래그 하나로 나무표시
 */
#define MA 100
int n;
char map[52][52];
bool visit[52][52];
int dp[52][52];
int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};
int dir; // 1이면 가로, -1이면 세로
int edir;
struct point{
    int row, col;
};
point center;
point dest;

void Display()
{
    cout << "--------------------" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
}

bool isBoundary(int r , int c)
{
    return r>=0 && r<n && c>=0 && c<n;
}

bool isTurn(int row, int col){
    for (int i = row-1; i <= row+1; ++i) {
        for (int j = col-1; j <= col+1; ++j) {
            if(!isBoundary(i,j)) continue;
            if(map[i][j] == '1') return false;
        }
    }
    return true;
}

bool isCenter(int row, int col ,int dir)
{
    if(dir == -1) // 세로
    {
        return row-1 >= 0 && row+1 < n && map[row-1][col] != '1' && map[row+1][col] != '1';
    } else{
        return col-1 >= 0 && col+1 < n && map[row][col-1] != '1' && map[row][col+1] != '1';
    }
}

int BackTracking(int row, int col, int cnt, int dir)
{
    if(!isBoundary(row,col)) return MA;
    if(!isCenter(row,col,dir)) return MA;
    if(dp[row][col] <= cnt) return dp[row][col];
    if(visit[row][col]) return MA;
    if(map[row][col] == '1') return MA;
    if(map[row][col] == 'E' && edir == dir) {
//        cout << row << "," << col << " cnt : " << cnt << " dir : " << dir << endl;
        return cnt;
    }
    int& ret = dp[row][col];

    for (int i = 0; i < 4; ++i) {
        ret = min(ret,BackTracking(row+dr[i],col+dc[i],cnt+1,dir));
    }

    if(isTurn(row,col)){
        dir = dir* -1; // 방향전환
        ret = min(ret,BackTracking(row,col,cnt+1,dir));
    }
    return ret;
}


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> n;
    int find_center = 0;
    int find_end = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> map[i][j];
            if(map[i][j] == 'B'  && find_center < 2){
                find_center++;
                if(find_center == 2){
                    if(center.row == i) dir = 1;
                    else dir = -1;
                }
                center = {i,j};
            }
            if(map[i][j] == 'E'  && find_end< 2){
                find_end++;
                if(find_end == 2){
                    if(dest.row == i) edir = 1;
                    else edir = -1;
                }
                dest = {i,j};
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dp[i][j] = MA;
        }
    }
//    cout << map[dest.row][dest.col] << endl;
//    cout << center.row << " " <<center.col << "," << dir <<endl;
//    cout << dest.row << " " <<dest.col << "," << edir <<endl;
    int ans = BackTracking(center.row,center.col,0,dir);
    if(ans == MA) cout << 0 << endl;
    else cout << ans+1 << endl;
}
