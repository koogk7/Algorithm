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

/* 15953 상금헌터
 * 회고
 *  - fillRewoard에서 범위를 start+ end - 1로 주고 있었다 혹시 병신인가?
 *  - 정답이 틀리면 모든 로직을 빼놓지 않고 다시 보자! 특히 범위 체크!
 */

int t, a, b;
int rewoardA[102];
int rewoardB[65];


void fillRewoard(int start, int end, int account, int* target){ // [start - end)
    for (int i = start; i < end; ++i) {
        target[i] = account;
    }
}

void test(){
    for (int i = 0; i < 22; ++i) {
        cout << rewoardA[i] << " ";
    }

    cout << endl;

    for (int i = 0; i < 32; ++i) {
        cout << rewoardB[i] << " ";
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    rewoardA[1] = 500;
    rewoardB[1] = 512;

    fillRewoard(2,4,300,rewoardA);
    fillRewoard(4,7,200,rewoardA);
    fillRewoard(7,11,50,rewoardA);
    fillRewoard(11,16,30,rewoardA);
    fillRewoard(16,22,10,rewoardA);

    fillRewoard(2,4,256,rewoardB);
    fillRewoard(4,8,128,rewoardB);
    fillRewoard(8,16,64,rewoardB);
    fillRewoard(16,32,32,rewoardB);

    cin >> t;

    while(t--){
        cin >> a >> b;
        int ans = (rewoardA[a] + rewoardB[b]) * 10000;
        cout << ans << "\n";
    }
}

