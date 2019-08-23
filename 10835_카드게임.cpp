// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
#include <map>
#include <math.h>
#include <stack>
#include "typeinfo"




using namespace std;

/*
 * 10835 카드게임
 *  - 처음에 순서에 따른 문제라서 que로 어떻게 해볼려고 했다.
 *  - que로 해볼려고 했던게 Backtracking했을 때 시간복잡도를 잘못 계산하고 있었다.
 *  - 시간 복잡도 N * N
 */

int n;
vector<int> leftCard;
vector<int> rightCard;
int dp[2001][2001]; // [left][right]일 때 최대점수

bool isScore(int leftNum, int rightNum){
    return rightNum < leftNum;
}


int BackTracking(int leftIdx, int rightIdx){
    if(leftIdx >= n or rightIdx >= n)
        return 0;

    int &ret = dp[leftIdx][rightIdx];
    if(ret != -1)
        return ret;


    if(isScore(leftCard[leftIdx], rightCard[rightIdx])){
        rightCard[rightIdx];
        ret = BackTracking(leftIdx, rightIdx + 1) + rightCard[rightIdx];
    } else{
        ret = max(BackTracking(leftIdx + 1, rightIdx), BackTracking(leftIdx + 1, rightIdx + 1));
    }

    return ret;

}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    int input;

    for (int i = 0; i < n; ++i) {
        cin >> input;
        leftCard.push_back(input);
    }

    for (int i = 0; i < n; ++i) {
        cin >> input;
        rightCard.push_back(input);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dp[i][j] = -1;
        }
    }

    cout << BackTracking(0,0);


}

