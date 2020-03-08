#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <stack>
#include <map>
#include <set>
#include <math.h>

typedef long long ll;

using namespace std;

/* 1124 언더프라임
 *
 * 난이도 중상
 * 1. end까지 소수를 구해놓는다. 각 자연수가 소수인지 bool으로 마킹
 * 2. i를 소수 분해
 *  2-1. i 로우바운드를 구함
 *  2-2. 구해놓은 소수들을 로우바운드 부터 나누어감
 *  2-3. 소인수 담은 배열 리턴
 * 3. 리턴 받은 배열의 크기를 isPrime 인덱스로 마킹해서 언더프라임인지 확인
 */
#define MAX_V 100002
int isPrime[MAX_V];
vector<int> primes;


void getPrime(int begin, int end){
    bool *c = new bool[end+1];
    c[1] = true;

    for(int i = 2; i*i<= end; i++){
        if(!c[i]){
            for(int j = i * i; j <= end; j+=i){
                c[j] = true;
            }
        }
    }
    
    for(int i = begin; i <= end; i++)
        if(!c[i]){
            primes.push_back(i);
            isPrime[i] = true;
        }
    delete[] c;
}

vector<int> decompose(int number){
    vector<int> ret;
    int maxPrimeIdx = int(lower_bound(primes.begin(), primes.end(), number) - primes.begin());
    if(maxPrimeIdx == primes.size())
        maxPrimeIdx--;

    while (number > 1) {
        if (number % primes[maxPrimeIdx] != 0) {
            maxPrimeIdx--;
            continue;
        }
        number = number / primes[maxPrimeIdx];
        ret.push_back(primes[maxPrimeIdx]);
    }
    return ret;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int begin, end;
    int ans = 0;
    cin >> begin >> end;

    getPrime(2,end);

    for (int i = begin; i <= end; ++i) {
        vector<int> underPrime = decompose(i);
        if(isPrime[underPrime.size()]) ans++;
    }
    cout << ans;

}










