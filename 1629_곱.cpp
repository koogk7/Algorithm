#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <stack>
#include <map>
#include <set>

typedef long long ll;


#define MAX_N 68
#define INF 987654321



using namespace std;

/*
 * 1629 곱
 * 자연수 A를 B번 곱한 수를 C로 나눈 나머지를 구해라
 * A,B,C가 겁나 큼
 *
 * 지수 법칙을 이용하는 것이 핵심
 * 10^10 을 구할 때, pow(10,10)은 10*10*10... 총 10번의 곱셈이 일어난다.
 * 그러나 지수를 절반씩 나누어서 구하면 아래와 같다
 * 10^10 = 10^5 * 10^5 // 10^5를 구해서 변수에 담아 곱해준다. 총 연산 1번
 * 10^5 = 10^2 * 10^2 * 10 // 2번
 * 10^2 = 10 * 10 // 1번
 * 총 5번의 연산만에 구할 수 있다. 이런식으로 재귀 한 단계마다 문제의 크기가 절반으로 줄어들기 때문에
 * 전체 문제의 수는 log n 이 된다.
 *
 * n == 짝수
 *  a^n = a^(n/2) * a^(n/2)
 * n == 홀수
 *  a^n = a^(n/2) * a^(n/2) * a
 *
 * 모듈러 연산 분배 법칙
 *  (a + b) mod n = ( (a mode n) + (b mode n) ) mode n
 *  (a * b) mod n = ( (a mode n) * (b mode n) ) mode n
 *  ex) 10*11 % 12 = ( ( 10 % 12 ) * (11 % 12) ) % 12
 */

int a,b,c;

// n에 대해 n^k를 리턴
int power(int n, int k){
    if(k==0) return 1;

    int temp = power(n,k/2);
    int result = (1LL * temp * temp) % c;

    if(k%2) result = 1LL * result * n % c;
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> a >> b >> c;
    cout << power(a,b);
}









