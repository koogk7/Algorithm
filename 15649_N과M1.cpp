#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
/*
 * cout << endl 을 이용할 경우 시간초과가 뜸
 * endl은 내부버퍼를 flash까지 시켜주기때문에 \n보다 훨씬 느리다!
 *  
 */

using namespace std;

int n,m;
int arr[11];
int select_index[11];

void Solution(int k)
{
    if(k == m) // m개 모두 선택시
    {
        for (int i = 0; i < m; ++i) { // 출력
            cout << arr[i]+1 << ' ';
        }
        cout << '\n';
        return;
    }

    for (int j = 0; j < n; ++j) {
        if(!select_index[j]) // j가 선택이 안됬다면
        {
            arr[k] = j;
            select_index[j] = 1;
            Solution(k+1);
            select_index[j] = 0; // k번째 수를 j로 정한 모든 경우 확인 후 j를 다시 초기화
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    Solution(0);

}