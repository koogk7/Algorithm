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
 * 2688 줄어들지 않아
 * 소요시간 : 22분분
 * - dp[2][2]는 2자릿수에서 맨 앞자리가 2가 왔을 때 이다.
 * 
 */
ll dp[65][10];

int main() {
    int t;

    for (int i = 0; i < 10; ++i) {
        dp[1][i] = 1;
        dp[2][i] = 10 - i;
    }

    for (int i = 3; i < 65; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int k = j; k < 10; ++k) {
                dp[i][j] += dp[i-1][k];
            }
        }
    }

    cin >> t;

    while(t--){
        int n;
        ll ans = 0;
        cin >> n;

        for (ll i = 0; i < 10; ++i) {
            ans += dp[n][i];
        }

        cout << ans << "\n";
    }

}









