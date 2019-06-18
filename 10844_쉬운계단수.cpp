// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;


/**
 * 10844번 쉬운 계단
 *
 *  회고
 * 1. 문제 자체는 어렵지 않았다. dp 갱신이 없는 문제임에도 갱신을 해줘서 초반에 버벅거림. dp갱신이 있는지 없는지 잘 파악!
 * 2. mod 연산 때문에 삽질을 했다. 또한 정답의 범위가 int 범위를 벗어난다.
 * int 자료형을 가질 수 있는 최대 범위는 2^32로 약 10^10 * 2 정도이다!
 * 3. 삽질노트
 *  ans += BackTracking() % mod 로 정답을 계산하고 있었음
 *  이렇게되니 큰값에 대해서는 당연히 정답이 틀리게 나옴
 */


int n;
long long dp[101][101];


void Display(string msg){
    cout<< "=====" << msg << "====" << endl;
    for (int i = 1; i < 10; ++i) {
        for (int j = 1; j < n+1; ++j) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
}

long long BackTracking(int number, int select){

    if(number > 9 || number <0) return 0;
    long long &ret = dp[number][select];
    if(select == n) {
        ret = 1;
        return ret;
    }
    if(ret != 0){
        return ret;
    }
    ret = (BackTracking(number+1, select+1) + BackTracking(number-1, select+1)) %  1000000000;

    return ret;

}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    long long ans = 0;
    cin >> n;
    for (int i = 1; i < 10; ++i) {
        ans = (ans + BackTracking(i,1)) % 1000000000;
    }

    cout << ans << endl;
//    Display("Debug");

}

