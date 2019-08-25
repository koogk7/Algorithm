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
#include "typeinfo"




using namespace std;

/*
 * 11375 열혈강호
 *      - 2차원 dp를 채워가면서 풀려고 했으나, 각 상황에 대해서 완료된 업무가 다 다르다
 *      - 즉 각 부분문제에 대해 독립성이 보장되지 않는다.
 *      - 해서 완료된 업무 경로를 dp에다 저장하고 비트연산으로 풀려고 시도, 그러나 이 경로들이 2^1000개가 나옴으로 포기
 *      - 완전탐색으로 구현할 경우 무조건 터진다.
 *      - 이분매칭을 이용해서 쉽게 풀 수 있는 문제
 */


int n,m;
vector<int> canTask[1011];
bool visit[1011];
int match[1011];

bool isMatching(int employee){ // 정점이 매칭 가능한지
    if(visit[employee]) return false;
    visit[employee] = true;

    for (int i = 0; i < canTask[employee].size(); ++i) {
        int task = canTask[employee][i];
        if(!match[task] || isMatching(match[task])){ // 매칭되지 않은 정점이거나 이미 매칭된 정점이 다른 정점과 매칭 가능 할때
            match[task] = employee; // 매칭
            return true;
        }
    }
    return false;
}

int binaryMatch(){
    int ret = 0;
    for (int i = 1; i < n+1; ++i) {
        memset(visit, 0, sizeof(visit));
        if(isMatching(i)) ret++;
    }
    return ret;
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    int taskNum;

    for (int i = 1; i < n+1; ++i) {
        cin >> taskNum;
        for (int j = 0; j < taskNum; ++j) {
            int input;
            cin >> input;
            canTask[i].push_back(input);
        }
    }

    cout << binaryMatch();

}

