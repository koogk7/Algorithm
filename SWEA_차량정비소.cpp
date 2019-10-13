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
#define INF 9876543210
/*
 * N개의 접수 창구번호,  M개의 정비 창구번호가 있다.
 *
 * 정비
 *  1. 접수 창구에서 고장 접수
 *  2. 정비 창구에서 차량을 정비
 *
 *  고객은 도착하는 대로 1번부터 고객번호를 부여 받는다.
 *  빈 접수 창구가 있으면 고장 접수, 없으면 기다림
 *  고장 접수를 완료하면 정비 창구로 이동
 *
 *  접수 창구의 우선순위
 *      1. 고객번호가 낮은 순서대로
 *      2. 빈 창구가 여러 곳인 경우, 접수 창구번호가 작은 곳으로
 *  정비 창구 의 우선순위
 *      1. 먼저 기다리는 고객 우선
 *      2. 동시에 접수를 완료 할 경우, 접수 창구 번호가 작은 고객 우선
 *      3. 빈 창구가 여러개 일 경우 정비 창구번호가 작은 곳으로
 *  지갑을 분실한 고객과 같은 접수 창구와 같은 정비 창구를 이용한 고객번호를 찾아 합을 출력
 *
 *  N, M = 9
 *  K = 1000, 창구번호 고객번호는 1부터 시작
 *
 *  두개의 큐를 둔다. 접수 창구는 일반 큐, 정비 창구는 우선순위 큐
 *  접수 창구, 정비 창구는 고객의 인덱스를 저장, 없을 때는 0
 *  접수 창구가 완료되면 정비 대기큐로
 *  정비가 완료되면 완료큐로
 *
 *
 */

int T;
int n,m,k;
int goal_reci, goal_fix;
struct Cust {
    int idx, arrive;
    int reci, fix;
};
struct cmp{
    bool operator()(Cust a, Cust b){
        if(a.arrive == b.arrive)
            return a.reci > b.reci;
        return a.arrive > b.arrive;
    }
};
struct Submit{
    int cust,deal, remain;
};

queue<Cust> reci_waitque;
priority_queue<Cust, vector<Cust>, cmp> fix_waitque;
queue<Cust> time_que;
vector<Cust> customs;
int complete_cnt;
vector<Submit> recipit;
vector<Submit> fix;
int sec;


void workRecipit(){

    while(!time_que.empty() and time_que.front().arrive == sec){
        reci_waitque.push(time_que.front());
        time_que.pop();
    }


    for (int i = 1; i < n+1; ++i) {

        if(recipit[i].remain > 0) { // 빈창구 있는지 확인

            recipit[i].remain--;
            if(recipit[i].remain != 0) continue;

            int cust_idx = recipit[i].cust;

            customs[cust_idx].arrive = sec;
            recipit[i].cust = -1;
            fix_waitque.push(customs[cust_idx]);
        }


        if(recipit[i].remain == 0 and !reci_waitque.empty()){
//        else if (!reci_waitque.empty()){
            // 창구 삽입
            Cust custom = reci_waitque.front();
            reci_waitque.pop();
            recipit[i].cust = custom.idx;
            recipit[i].remain = recipit[i].deal;
            customs[custom.idx].reci = i;
        }
    }

}

void workFix(){
    for (int i = 1; i < m+1; ++i) {

        if(fix[i].remain > 0) { // 빈창구 있는지 확인

            fix[i].remain--;
            if(fix[i].remain != 0) continue;

            int cust_idx = fix[i].cust;
            customs[cust_idx].arrive = sec;
            fix[i].cust = -1;
            complete_cnt++;
        }

        if(fix[i].remain == 0 and !fix_waitque.empty()){
//             창구 삽입
            Cust custom = fix_waitque.top();
            fix_waitque.pop();
            fix[i].cust = custom.idx;
            fix[i].remain = fix[i].deal;
            customs[custom.idx].fix = i;
        }
    }

}

int main(){
    cin >> T;

    for (int t = 1; t < T+1; ++t) {
        cin >> n >> m >> k >> goal_reci >> goal_fix;

        reci_waitque = queue<Cust>();
        fix_waitque = priority_queue<Cust, vector<Cust>, cmp>();
        recipit = vector<Submit>(n+1);
        fix = vector<Submit>(m+1);
        customs = vector<Cust>(k+1);
        complete_cnt = 0;
        sec = 0;
        int ans = 0;

        for (int i = 1; i < n+1; ++i) {
            cin >> recipit[i].deal;// 접수창구
        }

        for (int i = 1; i < m+1; ++i) {
            cin >> fix[i].deal;// 장비창구
        }

        for (int i = 1; i < k+1; ++i) {
            int arrive;// 고객 도착시간 입력
            cin >> arrive;
            time_que.push({i,arrive,-1,-1});
            customs[i] = {i,arrive,-1,-1};
        }

        while (complete_cnt < k){
            workRecipit();// 접수 창구 working
            workFix();// 정비 창구 working
            sec++;// sec++
        }

        for (int i = 1; i < k+1; ++i) {
            if(goal_reci == customs[i].reci and goal_fix == customs[i].fix)
                ans += i;
        }
        if(ans == 0)
            ans = -1;
        cout <<"#" << t << " " <<ans << "\n";

    }
}

