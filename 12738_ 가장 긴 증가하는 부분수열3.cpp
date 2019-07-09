// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
#include <map>
#include <math.h>
using namespace std;


/**
 * 12015번 가장 긴 증가하는 부분수열2
 *
 * 30분 걸림
 */
#define MAX_N 1000000
#define MIN_V -1000000000

int n;
int seq[MAX_N];
int dp[MAX_N]; // 크기가 i인 수열중 마지막 원소의 최솟값
int last;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> seq[i];
        dp[i] = MIN_V;
    }

    for (int i = 0; i < n; ++i) {
        if(dp[last] == seq[i]) continue;
        if(dp[last] < seq[i]) dp[++last] = seq[i];
        else{
            int lowerBound = int(lower_bound(dp, dp+last, seq[i]) - dp);
            dp[lowerBound] = seq[i];
        }
    }

    cout << last;


}

