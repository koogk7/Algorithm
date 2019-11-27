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
 * 9465 스티커
 * 소요시간 : 20분
 * - 스티커를 떼면 변을 공유하는 스티커는 모두 사용 할 수 없다.
 * - 점수의 합이 최대가 되게 스티커를 때야한다.
 * - n 10^6
 * - DP 아이디어 생각하기가 어려웠다.
 * - 문제를 작은 문제로 분할 하는 연습이 필요, 이 문제는 col단위로 분할
 */

int dp[100001][3];
int n;
int sticker[2][100001];
int ans;




int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;


    while(t--) {
        cin >> n;

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> sticker[i][j];
            }
        }

        ans = 0;
        dp[0][0] = sticker[0][0];
        dp[0][1] = sticker[1][0];
        dp[0][2] = 0;

        for (int i = 1; i < n; ++i) {
            dp[i][0] = dp[i - 1][1] + sticker[0][i]; // 이전에 0번 Row를 땜
            dp[i][0] = max(dp[i][0], dp[i - 1][2] + sticker[0][i]); // 이전에 스티커를 안땜

            dp[i][1] = dp[i - 1][0] + sticker[1][i]; // 이전에 0번 Row를 땜
            dp[i][1] = max(dp[i][1], dp[i - 1][2] + sticker[1][i]); // 이전에 스티커를 안땜

            dp[i][2] = max(dp[i - 1][0], dp[i - 1][1]);
        }

        for (int i = 0; i < 3; ++i) {
            ans = max(ans, dp[n - 1][i]);
        }

        cout << ans << "\n";
    }
}









