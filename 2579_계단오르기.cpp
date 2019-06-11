// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;


/**
 * 2579번 계단 오르기
 *
 * 뻘짓회고
 *  1. 처음에 2차원 dp를 통해 Top-down 형식으로 풀고자했다. 이 때 어느 조건으로 dp를 이용해 가지를 쳐야할지 어려워 방향을 회유했다.
 *  2. 최솟값을 구하는 경우는 중간에 가지치기가 가능함으로 Top-down으로 쉽게 풀 수 있으나,
 *  이 문제와 같이 최댓값을 찾는 dp문제일 경우 터미널 노드까지 가봐야 함으로 down-top을 먼저 생각해보자!
 */

int n;
int score[302];
int ans = 0;
int dp[302][2]; // col만큼 연속했을 때 row 계단을 밟았을 때 최댓값
int dp2[302];


int BackTracking(int cur_stair, int seq_cnt, int acc){
    if(cur_stair > n) return 0;
    if(cur_stair == n-2 && seq_cnt == 1) return 0; // 마지막 계단을 밟지못함
    if(cur_stair == n-1){
        dp[cur_stair][seq_cnt] = max(dp[cur_stair][seq_cnt], acc+score[cur_stair]);
        ans = max(ans, dp[cur_stair][seq_cnt]);
        return dp[cur_stair][seq_cnt];
    }

    if(seq_cnt == 1)
        dp[cur_stair][seq_cnt] = BackTracking(cur_stair+2,0, acc+score[cur_stair]);
    else
        dp[cur_stair][seq_cnt] = max(BackTracking(cur_stair+2,0, acc+score[cur_stair]),
                                     BackTracking(cur_stair+1,seq_cnt+1, acc+score[cur_stair]));

    return dp[cur_stair][seq_cnt];

}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> score[i];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 2; ++j) {
            dp[i][j] = -1;
        }
    }

    dp2[0] = score[0];
    dp2[1] = score[0]+score[1];
    dp2[2] = max(score[0],score[1]) + score[2];

    for (int k = 2; k < n; ++k) {
        dp2[k] = max(dp2[k-3] + score[k-1], dp2[k-2]) + score[k];
    }

    cout << dp2[n-1] << endl;
//    cout << BackTracking(0,0,0);

}

