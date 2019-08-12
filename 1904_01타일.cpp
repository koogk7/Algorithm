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

/*
 *
 *
 */


using namespace std;

int dp[1000000];
int n;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    dp[1] = 1;
    dp[2] = 2;

    for (int i = 3; i < n+1; ++i) {
        dp[i] = (dp[i-1] + dp[i-2]) % 15746;
    }

    cout << dp[n] << "\n";

}

