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
 * 미생물 격리
 * K개의 미생물 군집이 있다. 가장자리 부분에는 약품이 있음
 * 미생물 군집의 위치와, 군집 내 미생물 수, 이동방향
 *  1. 각 군집들은 1시간마다 이동방향에 있는 다음 셀로 이동
 *  2. 경계에 도착하면 미생물 절반이 죽고, 이동방향이 반대로 바뀜, 홀수인 경우는 몫만!
 *  3. 미생물이 0이면 군집삭제
 *  4. 두 개 이상의 군집이 겹치면 합쳐짐, 미생물이 많은 녀석의 방향을 따
 *
 *
 *  세 개 이상 충돌 했을 때 방향 설정하는데 문제가 있었다.
 */

int T;
int n,m,k;
int dr[] = {0,-1,1,0,0};
int dc[] = {0,0,0,-1,1};
struct Micro{
    int row, col, age, dir;
    bool isAlive;
};
int box[101][101];
int origin[101][101];
int grow[1001];
vector<Micro> micros;

bool isBoundary(int row, int col){
    return row == n-1 or row == 0 or col == n-1 or col == 0;
}

int reverse(int dir){
    if(dir == 1)
        return 2;
    if(dir == 2)
        return 1;
    if(dir == 3)
        return 4;

    return 3;
}

void moveOne(int idx){

    Micro &cur = micros[idx];

    int dir = cur.dir;
    int nr = cur.row + dr[dir];
    int nc = cur.col + dc[dir];

    if(isBoundary(nr,nc)){ // 경계
        cur.age /= 2;
        cur.dir = reverse(cur.dir);
        if(cur.age == 0){
            cur.isAlive = false;
            return;
        }
    }

    if(box[nr][nc] != -1){ // 미생물 겹침
        Micro &before = micros[box[nr][nc]];

        if(before.age > cur.age){
            cur.isAlive = false;
            grow[box[nr][nc]] += cur.age;
        } else{
            before.isAlive = false;
            grow[idx] += before.age;
            grow[idx] += grow[box[nr][nc]];
            box[nr][nc] = idx;
        }
    } else {
        box[nr][nc] = idx;
    }

    cur.row = nr;
    cur.col = nc;

}

void init(){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            origin[i][j] = box[i][j];
            box[i][j] = -1;
        }
    }

    for (int l = 0; l < k; ++l) {
        grow[l] = 0;
    }
}


int main(){
    cin >> T;

    for (int t = 1; t <= T; ++t) {
        cin >> n >> m >> k;

        int ans = 0;
        micros = vector<Micro>(k, {0,0,0,0,0});
        memset(box,-1, sizeof(box));
        memset(origin,-1, sizeof(origin));

        for (int i = 0; i < k; ++i) {
            int row,col,age,dir;
            cin >> row >> col >> age >> dir;
            micros[i] = {row,col,age,dir,true};
            box[row][col] = i;
        }

        for (int i = 0; i < m; ++i) {
            init();
            for (int j = 0; j < k; ++j) {
                if(!micros[j].isAlive) continue;
                moveOne(j);
            }

            for (int j = 0; j < k; ++j) {
                if(!micros[j].isAlive) continue;
                micros[j].age += grow[j];
            }
        }

        for (int i = 0; i < k; ++i) {
            if(!micros[i].isAlive) continue;
            ans += micros[i].age;
        }

        cout << "#" << t << " " << ans << "\n";
    }
}

