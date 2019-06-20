#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <stack>
#include <string.h>
#include <queue>
using namespace std;

int main(){
 int n;
 int T;
 ios_base::sync_with_stdio(0);
 cin.tie(NULL);
 cin >> T;
    for (int t = 0; t < T; ++t) {
        cin >> n;
        int dp[41][2] = {0};
        dp[0][0] = 1;
        dp[1][1] = 1;
        for (int i = 2; i < n+1; ++i) {
           dp[i][0] += dp[i-1][0] + dp[i-2][0];
           dp[i][1] += dp[i-1][1] + dp[i-2][1];
        }
        cout << dp[n][0] << " " << dp[n][1] << '\n';
    }

}
