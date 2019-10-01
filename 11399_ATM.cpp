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
#include <set>
#include <sstream>
#include <string.h>
using namespace std;
typedef long long ll;

/*
 * 11399 ATM
 *  줄을 서는 순서에 따라 시간의 합이 달라
 */

int n;
vector<int> times;

int main(){
    cin >> n;
    int input;
    int ans = 0;
    int acc = 0;

    times.resize(n);

    for (int i = 0; i < n; ++i) {
        cin >> times[i];
    }

    sort(times.begin(), times.end());

    for(auto time : times){
        acc += time;
        ans += acc;
    }

    cout << ans;

}

