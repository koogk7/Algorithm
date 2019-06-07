#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
/**
 *
 * 회고
 *  1. dr, dc 인덱스는 0부터 시작하고, 주사위 인덱스는 1부터 시작하는데 똑같은 값을 dr,dc에 넘겨주고 있어서 에러가 났음
 *  2. 주사위가 어떻게 바뀌는지 생각하는데 많은 시간 소요 40~50분 걸린듯
 *  3. 구현때는 1번의 실수 + box의 값을 안받고 있었음
 *  4. 처음 SetInfo 구현시, top값 갱신 빼먹었음
 *
 *
 * 지도가 존재, 이 지도위에 주사위가 하나 있다.
 * 주사위는 지도 위에 면이 1이고, 동쪽을 바라보는 방향이 3 인상태로 있다
 * 주사위 전개도
 *      2
 *    4 1 3 ---> 1,6    2,5     4,3
 *      5
 *      6
 *  가장 처음에 주사위는 모든면이 0
 *  이동한 칸에 값이 0이면 주사위의 바닫에 쓰여있는 수가 칸에 복사
 *  0이 아닌 경우에는 이 수가 주사위의 바닥을 복사, 칸에 있는 수는 0 이됨
 *  --> 주사위가 이동 할 때마다 상단에 씋여있는 값을 구해라
 *
 *  마주보고 있는 면은 합이 항상 7
 *      2
 *    1 3 6
 *      5
 *      4
 *  1 동쪽 2 서쪽 3 북쪽 4 남쪽  ---> 우좌상하
 *  주사위가 어떻게 움직여?
 *  주사위 바닥이 1일 때
 *  1. 남쪽, 1의 남쪽 5가 바닥이 되 , 4차이
 *  2. 동쪽, 1의 동쪽 3이 바닥이 되 , 2차이
 *  3. 북쪽, 1의 북쪽 2가 바닥이 되 , 1차이
 *  4. 서쪽, 1의 서쪽 4가 바닥이 되 , 3차이
 *
 *  주사위 바닥이 2 일때
 *  1. 남쪽, 2의 남쪽 1 바닥이되, 1차이
 *  2. 동쪽 ,2의 동쪽 3이 바닥이되 1차이
 *
 *  주사위 각 번호에 따라 동서남북이 정해져있네?
 *  전개도 모양을 저장을 할까? 전개도 모양만 알고 있으면 주사위가 어떻게 굴러가는지 알 수 있지
 *  전개도 모양은 어떻게 저장해?
 *  3개의 좌표만 알면 되, 첫번째는 바닥, 바닥의 왼쪽 ,바닥의 위쪽 x
 *  첫번째 오른쪽 두번째 왼쪽 세번째 위쪽 네번째 아래쪽
 *
 *  바닥이 1 일때, 왼쪽 : 4 , 위쪽 : 2
 *  바닥이 2 일때, 왼쪽 : 4 , 위쪽 : 6
 *  바닥이 3 일때, 왼쪽 : 1 , 위쪽 : 2
 *
 *  바닥의 보수자리랑 현재방향녀석이랑 자리가 바꾸네!
 *  0, 3, 1, 2, 4, 5
 *  --> 남쪽으루 굴려 4
 *  3,0,-,-,5,4
 *
 */

using namespace std;

struct _dice{
    int row, col;
    int value[7] = {0,0,0,0,0,0,0}; // 1index 사용, 값을 저장
    int direct[7] = {-1,0,3,1,2,4,5}; // 방향정보
    int top = 6;
};

int box[22][22];
int dr[] = {0,0,-1,1};
int dc[] = {1,-1,0,0};
int n, m, t;
_dice dice;
int dir_list[1002];

void Print()
{
    cout << endl;
    cout << "Value : ";
    for (int i = 0; i < 7; ++i) {
        cout << dice.value[i] << " ";
    }
    cout << endl;
    cout << "Direct : ";
    for (int i = 0; i < 7; ++i) {
        cout << dice.direct[i] << " ";
    }
}

bool isBoundary(int r, int c)
{
    return r>=0 && r<n && c>=0 && c<m;
}

int Comple(int a)
{
    return abs(7-a);
}

void SetInfo(int dir){
    for (int i = 1; i < 7; ++i) {
        if(dice.direct[i] == dir)
        {
            int top = dice.top;//1. 현재바닥과의 상단면의 방향을 찾습니다.
//            cout << "Cur : " << dir << " Top : " << top << endl;
            dice.direct[top] = dir; // 탑의 방향을 바꿔주고
            dice.direct[Comple(top)] = dice.direct[Comple(i)]; // 바닥의 방향도 바꿔줌
            dice.direct[i] = 0; // 바닥으로
            dice.direct[Comple(i)] = 5; // 탑으로
            dice.top = Comple(i);
//            Print();
            break;
        }
    }
}

void Move(int dir)
{
    int nr = dice.row + dr[dir-1];
    int nc = dice.col + dc[dir-1];
    dice.row = nr;
    dice.col = nc;
}

void SetValue()
{
    int bottom = Comple(dice.top);
//    if(dice.value[bottom] == 0)
    if(box[dice.row][dice.col] == 0){
        box[dice.row][dice.col] = dice.value[bottom];
    } else {
        dice.value[bottom] = box[dice.row][dice.col];
        box[dice.row][dice.col] = 0;
    }

}

int main(){

    cin >> n >> m;
    cin >> dice.row >> dice.col >> t;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> box[i][j];
        }
    }

    for (int i = 0; i < t; ++i) {
        cin >> dir_list[i];
    }

    for (int i = 0; i < t; ++i) {
        int cur_dir = dir_list[i];
        int nr = dice.row + dr[cur_dir-1];
        int nc = dice.col + dc[cur_dir-1];
        if(!isBoundary(nr,nc)) continue;
        SetInfo(cur_dir);//전개도 모양설정
        Move(cur_dir);// 굴리고
        SetValue();// 값변경
        cout << dice.value[dice.top] << endl;
    }

}

