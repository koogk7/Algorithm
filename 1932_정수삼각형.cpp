// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;


/**
 * 1932번 정수 삼각형
 *
 * 뻘짓회고
 *  1. 마지막 depth dp값을 저장하지 않고 있었다.
 *  2. dp의미와 다른 값들이 저장되고 있었다.... 항상 dp에 어떤 값이 들어가는지 인지하자!
 *  3. 초기값을 0으로 잡아서, 실제로 합산값이 0일때도 더 깊이 들어가는 경우 발생, dp초기값은 절대 나올 수 없는 값으로!
 */

int n;
int costs[502][502];
int dp[502][502];


int BackTracking(int depth, int col){
    if(depth == n-1){
        dp[depth][col] = costs[depth][col];
        return dp[depth][col];
    }
    if(dp[depth][col] != -1) return dp[depth][col];


    dp[depth][col] = max(BackTracking(depth+1,col+1), BackTracking(depth+1,col)) + costs[depth][col];

    return dp[depth][col];

}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dp[i][j] = -1;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i+1; ++j) {
            cin >> costs[i][j];
        }
    }

    cout << BackTracking(0,0) << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i+1; ++j) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }

}

