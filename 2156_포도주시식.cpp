// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;


/**
 * 2156번 포도주 시식
 *
 *  회고
 * 1. 현재 포도주를 안 먹고 진행하는 경우를 배제하고 있었음
 */


int n;
int dp[10001][2];
int wine_amount[10001];

void Display(string msg)
{
    cout << "====" << msg << "====" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
}

int Backtracking(int wine, int seq_cnt){
    if(seq_cnt == 2) return 0;

    int &ret = dp[wine][seq_cnt];

    if(wine == n-1) {
        ret = wine_amount[wine];
        return  ret;
    }
    if(wine == n-2 && seq_cnt == 1) {
        ret = wine_amount[wine];
        return ret;
    }

    if(wine > n-1) return 0;

    if(ret != 0)
        return ret;

    ret += max(Backtracking(wine+1,seq_cnt+1), Backtracking(wine+2,0)) + wine_amount[wine];
    ret = max(ret, Backtracking(wine+1,0));

    return ret;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> wine_amount[i];
    }

    int ans = max(Backtracking(0,0), Backtracking(1,0));

    cout << ans << endl;

}

