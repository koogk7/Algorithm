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

int n;
bool candicate[1000];

int countStrike(int target, int compare){
    int rst = 0;

    for (int digit = 100; digit > 0; digit /= 10) {
        if(target/digit == compare/digit) // strike 카운트
            rst++;
        target %= digit;
        compare %= digit;
    }

    return rst;
}

int countBall(int target, int compare){
    bool isTarget[11];
    int rst = 0;

    for (int i = 0; i < 11; ++i) {
        isTarget[i] = false;
    }

    for (int digit = 100; digit > 0; digit /= 10) {
        int target_digit = target/digit;
        isTarget[target_digit] = true;
        target %= digit;
    }

    for (int digit = 100; digit > 0; digit /= 10) {
        int compare_digit = compare/digit;
        if(isTarget[compare_digit]) rst++;
        compare %= digit;
    }

    return rst;

}

bool isValid(int number){
    set<int> digits;
    string str_number = to_string(number);

    for (int i = 0; i < 3; ++i) {
        if(str_number[i] == '0') break;
        digits.insert(str_number[i] - '0');
    }

    return digits.size() == 3;
}

int main(){

    cin >> n;
    int number;
    int strike, ball;
    int compare;
    int ans = 0;

    for (int i = 123; i < 1000; ++i) {
        candicate[i] = true;
    }

    while(n--){
        cin >> number >> strike >> ball;

        for (int i = 123; i < 1000; ++i) {
            int candi_strike = countStrike(i, number);
            int candi_ball = countBall(i, number) - candi_strike;
            if(strike != candi_strike or candi_ball != ball)
                candicate[i] = false;
        }
    }

    for (int i = 123; i < 1000; ++i) {
        if(!isValid(i)) continue;
        if(candicate[i]) ans++;
    }

    cout << ans;


}

