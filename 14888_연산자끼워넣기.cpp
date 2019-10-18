// ConsoleApplication2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*

*/
#define INF 987654321
#define NINF -987654321
typedef long long ll;

int n;
ll maxValue = NINF;
ll minValue = INF;
vector<ll> numbers;
int operCnt[4];
int operTotal;

ll operate(int i, ll number1, ll number2) {
    if (i == 0) {
        return number1 + number2;
    }

    if (i == 1) {
        return number1 - number2;
    }

    if (i == 2) {
        return number1 * number2;
    }

    if (i == 3) {
        return number1 / number2;
    }

    return -1;
}

void dfs(int idx, ll value, int depth) {

    if (depth == n-1) {
        maxValue = max(maxValue, value);
        minValue = min(minValue, value);
        return;
    }

    if (idx >= n - 1)
        return;


    for (int i = 0; i < 4; i++)
    {
        if (operCnt[i] == 0)
            continue;

        ll next = operate(i, value, numbers[idx+1]);

        operCnt[i]--;
        dfs(idx + 1, next, depth + 1);
        operCnt[i]++;
    }

}


int main()
{
    cin >> n;

    numbers = vector<ll>(n);

    for (int i = 0; i < n; i++)
    {
        cin >> numbers[i];
    }

    for (int i = 0; i < 4; i++)
    {
        cin >> operCnt[i];
    }


    dfs(0, numbers[0], 0);

    cout << maxValue << "\n" << minValue << "\n";


}
