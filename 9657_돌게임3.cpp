// ConsoleApplication2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <stack>
#include <map>
#include <set>

using namespace std;

typedef long long ll;

/* 배열 90도 회
 */

#define MAX_N 68
#define INF 987654321

// ConsoleApplication2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <stack>
#include <map>
#include <set>

using namespace std;

/*
 * 9657 돌 게임 3
 * - 시간 : 22분
 * - 턴을 번갈아가면서 1,3,4 만큼 가져감
 * - 마지막 돌을 가져가는 사람이 게임이 이기게 된
 * - dp[i]는 dp[i-1],dp[i-3],dp[i-4] 모두 true 일 때 false가 된다.
 * ( 상대방 차례 때 이길 수 있는 방법 밖에 없다면 당연히 내가 진다.)
 */

bool dp[1001];

int main() {
    int n;

    cin >> n;
    dp[1] = true;
    dp[2] = false;
    dp[3] = true;
    dp[4] = true;

    for (int i = 5; i <= n; ++i) {
        if(!dp[i-1] or !dp[i-3] or !dp[i-4])
            dp[i] = true;
    }

    if(dp[n] == 1)
        cout << "SK";
    else
        cout << "CY";

}





