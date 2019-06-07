#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
/*
 * 도포 후 일정 시간 배양시킨 후 줄기세포의 개수가 몇개?
 *
 * 초기상태 : 비활성상태, 생명력수치가 x, --> x 시간동안 비활성 상태, 이후 활성
 * 활성상태 : x시간 이후 사망, 첫 1시간동안 상하좌우 번식
 * 죽은 상태로 셀을 차지
 * 하나의 셀에는 하나의 세포만!
 * 두개 이상의 세포가 동시에 번식할려한다면 생명력 수치가 높은 세포!
 *
 * 배양용기의 크기가 무제한....
 * k의 범위 300
 * n의 범위 50
 *
 * 세포가 있는 배열 visit와 생명력을 체크할 배열 box
 *
 *
 * 비활성 --> 활성 : box에서 생명력을 회수마다 --, 0이되면 xxx
 * 큐를 두개 준비해, 비활성 큐, 활성 큐
 *
 *  1. 입력과 동시에 비활성큐에 넣는다.
 *      번식먼저!
 *  2. while문 안에서, 큐안에 sec 체크
 *  3. 활성화가 생기면 활성화 큐에 삽입, state에 표시하고, 번식시작
 *  4. while문은 k시간만큼!
 *
 *  근데 왜 큐에 넣어? 일단 삽입,삭제 연산이 많아, 그리고 업데이트가 많아
 *  우선순위큐! 뭐를 기준으로? 초를 기준으로??? -- X
 *  큐를 쓸려고 하니 할때마다 빼줘야해... 최악의 시간복잡도 k* 셀의 수
 *  벡터쓰자 이것도 .... 삭제가 힘드네
 *
 *
 */

using namespace std;

struct sell{
    int row, col, time;
};

int n,m,k;
int t;
int box[700][700]; // 생명력을 저장합니다.
int state[700][700]; // 그리드에 세포가 있는지를 확인합니다. -1: 후보 ,0 : 없음, 1: 바활성, 2: 활성, 3:사망
vector<sell> wait_sell; // 비활성화 세포를 저장
vector<sell> alive_sell; // 활성화 세포를 저장
int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};
int ans;


void Print()
{
    cout << "----------Box-----------------" <<endl;
    for (int i = 0; i < n+(2*k); ++i) {
        for (int j = 0; j < m+(2*k); ++j) {
           cout << box[i][j] << " ";
        }
        cout << endl;
    }

    cout << "----------State-----------------" <<endl;
    for (int i = 0; i < n+(2*k); ++i) {
        for (int j = 0; j < m+(2*k); ++j) {
            cout << state[i][j] << " ";
        }
        cout << endl;
    }
}

void TimePlus()
{
//    cout << "--------Wait---------" <<endl;
    for (int i = 0; i < wait_sell.size(); ++i) {
        wait_sell[i].time++;
//        cout << "row : " << wait_sell[i].row << " col: " << wait_sell[i].col << " time: " << wait_sell[i].time <<endl;
    }

//    cout << "---------Alive-------------" <<endl;
    for (int i = 0; i < alive_sell.size(); ++i) {
        alive_sell[i].time++;
//        cout << "row : " << alive_sell[i].row << " col: " << alive_sell[i].col << " time: " << alive_sell[i].time <<endl;

    }
}

void CheckState()
{
    int row, col;
    for (int i = 0; i < wait_sell.size();) {
        row = wait_sell[i].row;
        col = wait_sell[i].col;
        if(wait_sell[i].time == box[row][col]) { // 활성화
            alive_sell.push_back({row, col, 0}); // 타임은 다시 0으로
            state[row][col] = 2; // 활성화
            wait_sell.erase(wait_sell.begin()+i); // 배열삭제
        } else {
            i++;
        }
    }
}

void Born()
{
    int row, col;
    int max;
    queue<sell> trans;
    for (int i = 0; i < alive_sell.size(); ++i) {
        row = alive_sell[i].row;
        col = alive_sell[i].col;
        if(alive_sell[i].time == 1){ // 번식
            int nr, nc;
//            cout<<"경계---------" <<endl;
            for (int j = 0; j < 4; ++j) {
                nr = row+dr[j];
                nc = col+dc[j];
                if(nr < 0 || nc < 0) continue;
                if(state[nr][nc] > 0) continue; // 이미 세포가 존재
                int cur = box[row][col];
//                cout <<  box[nr][nc] <<" r : " << nr << " c :" << nc << endl;
                box[nr][nc] = box[nr][nc] > cur ? box[nr][nc] : cur;
                if(state[nr][nc] == 0){
                    trans.push({nr,nc,0});
                    state[nr][nc] = -1;
                }
            }
        }
        if(alive_sell[i].time == box[row][col]){ // 사망
            state[row][col] = 3;
            alive_sell.erase(alive_sell.begin() + i);
            ans--;
            i--;
        }
    }

    while(!trans.empty()) // state 변경
    {
        row = trans.front().row;
        col = trans.front().col;
//        cout << "r : " << row << " c : " <<col <<endl;
        trans.pop();
        state[row][col] = 1;
        wait_sell.push_back({row,col,0});
        ans++;
    }
}

void Init()
{
    for (int i = 0; i < n+(2*k); ++i) {
        for (int j = 0; j < m+(2*k); ++j) {
            box[i][j] = 0;
        }
    }

    for (int i = 0; i < n+(2*k); ++i) {
        for (int j = 0; j < m+(2*k); ++j) {
            state[i][j] = 0;
        }
    }

    wait_sell.clear();
    alive_sell.clear();
    ans = 0;
}

int main(){

    cin >> t;
    int i = 1;
    while(t--)
    {
        cin >> n >> m >> k;

        for (int i = k; i < n+k; ++i) {
            for (int j = k; j < m+k; ++j) {
                cin >> box[i][j];
                if(box[i][j] != 0) {
                    state[i][j] = 1; // 비활성상태로 저장
                    wait_sell.push_back({i,j,0}); // 비활성화 큐에 삽입
                    ans++;
                }
            }
        }
        int q = k;
        while(q--) // k시간만큼
        {
//            cout << "------------" << q << "-------------------" <<endl;
            TimePlus();// time++
            Born();//번식
            CheckState();//state체크
//            Print();
        }
        cout << "#" <<i++ <<" " <<ans << endl;
       Init();
    }

}

