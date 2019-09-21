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
/*
 * 3079 입국심사
 *  - 45분 걸림, MAX값을 큰 수로 주니까 두가지 문제가 발생
 *      1. 제출 할 때 답이 틀림
 *      2. total을 int로 받고 있어서 오버플로우 발생, 고쳐도 틀림
 *      3. 그래서 max를 나올 수 있는 가장 큰 값으로 고침
 *  - 처음 완전탐색으로 시간초과 나옴
 *  - 바이너리 서치문제인걸 생각하는데 오래 걸림
 *  - 범위가 커 n^2이 힘든 서치의 경우 바이너리 서치를 생각하자
 */


typedef long long ll;

ll n,m;
vector<ll> judges;
ll max_sec = 0;

ll bSearch(int wait_people){
    ll start = 1;
    ll end = max_sec;
    ll mid = 0;

    while(start <= end){
        ll total = 0;
        mid = (start + end) / 2;

        for(auto i : judges){
            total += mid / i;
        }

        if(total < wait_people) start = mid + 1;
        else end = mid - 1;
    }

    return start;
}


int main(){

    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        ll input;
        cin >> input;
        judges.push_back(input);
        max_sec = max(max_sec, input);
    }

    max_sec *= m;

    sort(judges.begin(), judges.end());


    cout << bSearch(m) << "\n";

}

