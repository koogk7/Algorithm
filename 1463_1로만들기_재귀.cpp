#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <stack>
#include <string.h>
#include <queue>
using namespace std;

vector<int> dp;

int Make(int n){
    if(dp[n] != -1) return dp[n];
    int ret = 100000000;
    if(n % 3 == 0) ret = min(ret, Make(n/3));
    if(n % 2 == 0) ret = min(ret, Make(n/2));
    ret = min(ret, Make(n-1));
    dp[n] = ret + 1;
    return  dp[n];
}

int main(){
 int n;
 ios_base::sync_with_stdio(0);
 cin.tie(NULL);
 cin >> n;
 dp = vector<int>(n+1,-1);
 dp[1] = 0; dp[2] = 1; dp[3] = 1;
 cout << Make(n) << endl;

}
