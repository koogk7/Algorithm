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
 * 1744 수묶기
 *
 * 양수만 있을 때 --> 무조건 큰수끼리 묶는게 최고
 * 양수, 음수 존재 --> 정렬해서, 음수끼리 묶고, 양수끼리 묶고 절대값 기준으로!
 *
 * 생각보다 예외 케이스가 많다. 항상 반례를 생각해보자
 */

int n;
vector<ll> plus_numbers;
vector<ll> minus_numbers;

int main(){

    cin >> n;
    ll input;
    bool existZero = false;

    ll ans = 0;

    for (int i = 0; i < n; ++i) {
        cin >> input;
        if(input == 0) existZero = true;
        else if(input < 0)
            minus_numbers.push_back(input);
        else
            plus_numbers.push_back(input);
    }

    //sort
    sort(plus_numbers.begin(), plus_numbers.end(), [](ll a, ll b){
       return a > b;
    });

    sort(minus_numbers.begin(), minus_numbers.end());

   //양수 묶기, 절대값 기준
    ll temp = 0;
    for (int i = 0; i < plus_numbers.size(); ++i) {
        if(i%2 == 1) { // 홀수 일 때 곱하고
            if(temp == 1 and plus_numbers[i] == 1) // 1*1 < 1+1이 크다
                temp = 2;
            else if(plus_numbers[i] == 1) // n*1 < n + 1
                temp +=1;
            else
                temp *= plus_numbers[i];
        }

        else{ // 짝수일 때 더한다
            ans += temp;
            temp = plus_numbers[i];
        }
    }

    ans += temp;

   //음수 묶기, 절대값 기준
    temp = 0;
    for (int i = 0; i < minus_numbers.size(); ++i) {
        if(i%2 == 1) // 홀수 일 때 곱하고
            temp *= minus_numbers[i];
        else{ // 짝수일 때 더한다
            ans += temp;
            temp = minus_numbers[i];
        }
    }
    if(temp < 0 and existZero)
        temp = 0;
    ans += temp;

    cout << ans;


}

