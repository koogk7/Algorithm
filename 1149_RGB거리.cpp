// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;


/**
 * 1149번 RGB 거리
 *
 * 뻘짓 회고
 * 1. dp값 갱신을 안하고 있었음
 * 2. dp row, col 을 반대로 주고 있었음
 * 3. 불필요한 호출을 계속함, 항상 트리의 마지막 부분을 직접 그려서 어떤 상황이 되는지 유추해보자. 또 불필요한 호출 없는지 확인!
 * 4. 이 문제 같은 경우는 dp에 값이 갱신되면, 갱신된 부분 이하로는 절대 다시 탐색 할 필요가 없다!
 *
 */
#define MAX_V 987654321
int n;
int dp[1000][3]; // col : 색, row : 집번호, row 집번호가 col 색일 때 최소비용을 저장
int costs[1000][3];
int ans = MAX_V;


int BackTracking(int house_number, int color){
    if(dp[house_number][color] != MAX_V) return dp[house_number][color];
    if(house_number == n-1){
        dp[house_number][color] = costs[house_number][color];
        return dp[house_number][color];
    }

    dp[house_number][color] = min(BackTracking(house_number + 1, (color + 1) % 3),
            BackTracking(house_number + 1, (color + 2) % 3))  + costs[house_number][color];
    return dp[house_number][color];

}

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> costs[i][j];
            dp[i][j] = MAX_V;
        }
    }

    for (int color = 0; color < 3; ++color)
    {

        ans = min(ans,BackTracking(0,color));
    }

    cout << ans << endl;
}
