#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/*
 *
 */
#define MA 10000000
int T;
int n;
int map[10][10];
struct point{
    int row, col;
    int stair;
};
struct Stair{
    int row, col;
};
vector<point> people;
Stair stay[2];
int pidx; // 사람 인덱스
int ans = MA;


int getMove(int p, int s){
    return abs(people[p].row-stay[s].row) + abs(people[p].col-stay[s].col);
}

void Display()
{
//    cout << "------------------------------" << endl;
//    int idx = 0;
//    for(auto i: people){
//        if(idx == pidx) break;
//        cout << i.sec << " " << i.stay << " " << i.isStay << endl;
//        idx++;
//    }
}

int getSec(int sidx){
    int cnt = 0;
    priority_queue<int,vector<int>,greater<int>> moveQue;// 이동거리를 저장한 큐
    int downTime = map[stay[sidx].row][stay[sidx].col];

    for (int i = 0; i < pidx; ++i) {
        if(people[i].stair == sidx)
            moveQue.push(getMove(i,sidx));
    }
    queue<int> stairQue;
    queue<int> watingQue;


    while(1){
        if(moveQue.empty() && stairQue.empty() && watingQue.empty()) break;
        if(cnt > ans) break;
        cnt++;

        if(!stairQue.empty()){
            int completeTime = stairQue.front() + downTime;
            while(cnt == completeTime){
                stairQue.pop();
                completeTime = stairQue.front() + downTime;
                if(stairQue.empty()) break;
            }
            if(stairQue.size() < 3 && watingQue.size() > 0){
                while(stairQue.size() < 3){
                    stairQue.push(cnt); // 도착시간 + 기다린 시간 = 현재시간
                    watingQue.pop();
                    if(watingQue.empty()) break;
                }
            }
        }

        //계단 내려가기
        while(cnt == moveQue.top()){ // 동시에 도착하는 사람이 있을 수 있음으로 while문
            if(stairQue.size() < 3){
                stairQue.push(moveQue.top()+1); // 1분후 내려감
                moveQue.pop();
            } else{
                watingQue.push(moveQue.top());
                moveQue.pop();
            }
            if(moveQue.empty()) break;
        }

    }


    return cnt;
}

int BackTracking(int idx){
    if(idx > pidx){
        int sec = getSec(0);
        sec = max(sec,getSec(1));
        ans = min(ans,sec);
        return ans;
    }
    int ret = MA;

    people[idx].stair = 0;
    ret = min(ret,BackTracking(idx+1));
    people[idx].stair = 1;
    ret = min(ret,BackTracking(idx+1));

    return ret;

}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> T;

    for (int t = 0; t < T; ++t) {
        cin >> n;
        pidx = 0;
        int sidx =0;
        people = vector<point>(11);
        ans = MA;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> map[i][j];
                if(map[i][j] == 1)
                    people[pidx++] = {i,j,-1};
                else if(map[i][j] >= 2)
                    stay[sidx++] = {i,j};
            }
        }
        cout << "#" << t+1 << " " <<BackTracking(0) << endl;
    }
}