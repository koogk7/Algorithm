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

#define MAX 2000001

int n;
bool no_prime[MAX];

bool isPalindrome(int number){

    int reverse_number = 0;

    for (int digit = number;  digit > 0; digit /= 10) {
        reverse_number = reverse_number*10 + digit % 10;
    }

    return number == reverse_number;
}


int main(){

    cin >> n;

    no_prime[0] = 1;
    no_prime[1] = 1;

    for (int i = 2; i < MAX; ++i) { // 에라토네스의 체
        if(no_prime[i]) continue;
        for (int j = i+i; j < MAX; j += i) {
            no_prime[j] = true;
        }
    }

    for (int i = n; i < MAX; ++i) {
        if(no_prime[i]) continue;
        if(isPalindrome(i)){
            cout << i << "\n";
            break;
        }
    }


}

