#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <stack>
#include <string.h>
#include <queue>
#include <set>
using namespace std;

#define MA 10000000
int T;
int day,month,month3, year;
vector<int> use = vector<int>(12,0);

int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> T;

    for (int t = 0; t < T; ++t) {
        cin >> day >> month >> month3 >> year;
        int dp[13];
        dp[0] = 0;
        for (int i = 1; i < 13; ++i) {
            cin >> use[i];
            dp[i] = MA;
        }
        dp[1] = min(day*use[1], month);
        dp[2] = dp[1] + min(day*use[2], month);
        dp[2] = min(dp[2], month3);
        for (int i = 3; i < 13; ++i) {
            dp[i] = dp[i-1] + min(use[i]*day,month);
            dp[i] = min(dp[i], dp[i-3]+month3);
            dp[i] = min(dp[i],year);
        }
        cout<< "#" << t+1 << " " << dp[12] << endl;
//        for(auto i : dp) cout << i << " ";
    }


}
