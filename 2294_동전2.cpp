#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <stack>
#include <string.h>
#include <queue>
using namespace std;
#define MAX_S 10000000
vector<int> coin;
vector<int> dp;

int n,k;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> n >> k;
    coin = vector<int>(n,0);
    dp = vector<int>(k+1,MAX_S);
    for (int i = 0; i < n; ++i) {
        cin >> coin[i];
    }
    dp[0] = 0;
    for (int i = 1; i <= k; ++i) {
        for (int j = 0; j < n; ++j) {
            if(i-coin[j] < 0) continue;
            dp[i] = min(dp[i],dp[i-coin[j]]+1);
        }
    }
    if(dp[k] == MAX_S) cout << "-1" << endl;
    else cout << dp[k] << endl;

}
