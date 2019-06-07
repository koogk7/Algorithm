#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>
#include <stack>
using namespace std;

/*
 * 축구는 평일 오후에 하고 의무 참석도 아님
 * 축구를 하기 위해 모인 사람은 총 n 명, n은 짝수
 * 팀을 나눠야 해
 *
 * 능력치 s[i][j]는 i번 사람과 j번  사람이 같은 팀에 속했을 때 팀에 더해지는 능력치
 * 팀의 능력치는 팀에 속한 맴버에 s[i][j] 값의 합
 * s[i][j] , s[j][i]는 다를 수 있다!!!!
 *
 * 스타트와 링크 팀의 능력치 차이를 최소로 할려고 한다.
 *
 * 완전탐색 밖에 생각이 안나는데?
 *     n명중의 n/2를 뽑는 경우의 수 : 20*19~~/10! < 10000 충분
 */

int n;
int box[22][22];
int team[22];


int getGap()
{
    int stark = 0;
    int ringk = 0;
    for (int i = 0; i < n; ++i) {
        int team_flag = team[i];
        for (int j = 0; j < n; ++j) {
            if(team_flag == team[j]){
                if(team_flag == 0)
                    stark += box[i][j];
                else
                    ringk += box[i][j];
            }
        }

    }
    return abs(stark-ringk);

}


int BackTracking(int member, int depth)
{
    if(member >= n) return 100000;
    if(depth == n/2){
        return getGap();
    }
    int ret = 100000;

    team[member] = 1;
    ret = min(ret,BackTracking(member+1,depth+1));

    team[member] = 0;
    ret = min(ret,BackTracking(member+1,depth));

    return ret;

}


int main() {

    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> box[i][j];
        }
    }

    cout << BackTracking(0,0) << endl;

}

