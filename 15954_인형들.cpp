// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
#include <map>
#include <math.h>
using namespace std;

/*
 */
#define INF 9999999999999999

int n,k;
long long dolls[501];
long double ans = INF;

/*
 * 15954 회고
 *  - 처음에 자료형으로 double을 사용했다...
 *  - 분산의 최댓값이 얼마나 나올 수 있는 지 체크를 안했다.
 *  - K개만 뽑고있었다...
 *  - N을 넘어가는 범위가 계산에 포함될 수 있는데, 이것에 대한 예외 처리를 하지 않음
 *
 *  배운 것
 *     - 문제를 반드시 꼼꼼히 읽자
 *     - 인풋, 아웃풋 최댓값을 항상 체크
 *     - cout.precision(12) 를 통해 소수점 출력 자리를 결정 할 수 있다.
 *     - 문제의 예외가 없는지, 예외처리가 되었는지를 체크
 */


long double getStandard(int start, int seq){
    long double variance = 0;
    long double sum = 0;
    long double mean = 0;

    if(start + seq > n) return INF;

    for (int i = start; i < start + seq; ++i) {
        sum += dolls[i];
    }

    mean = sum / double(seq);

    for (int i = start; i < start + seq; ++i){
        variance += (dolls[i]-mean)*(dolls[i]-mean);
    }

    variance = variance / double(seq);

    return sqrt(variance);
}



int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;
    cout.precision(12);

    for (int i = 0; i < n; ++i) {
        cin >> dolls[i];
    }

    for (int i = 0; i < n; ++i) {
        for (int seq = k; seq <= n; ++seq) {
            ans = min(ans, getStandard(i,seq));
        }
    }

    cout << ans;
}

