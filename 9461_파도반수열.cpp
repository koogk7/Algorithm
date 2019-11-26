#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <stack>
#include <map>
#include <set>

typedef long long ll;


#define MAX_N 68
#define INF 987654321



using namespace std;

/*
 * 9461 파도반 수열
 * 소요시간 : 20분
 * - 규칙 찾는게 어려웠다
 * - 경계값을 항상 확인하자, int 범위를 벗어나 100을 넣으니 터졌다
 */

ll dp[101];

int main() {
    int t;

    dp[1] = 1;
    dp[2] = 1;
    dp[3] = 1;
    dp[4] = 2;
    dp[5] = 2;
    for (int i = 6; i <= 100; ++i) {
        dp[i] = dp[i-1] + dp[i-5];
    }

    cin >> t;

    while(t--){
        int n;
        cin >> n;
        cout << dp[n] << "\n";
    }

}









