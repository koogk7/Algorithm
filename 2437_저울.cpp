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
 * 2437 저울
 *  - 처음에 도저히 감이 안잡혀, 힌트를 봄 그리디!
 *  - 큰 무게부터 빼면서 하니 시간초과 --> dp 생각, 그러나 각 상황마다 남은 추가 달라서 불가능
 *  - 1~k 무게까지 만들 수 있을 때, w 추가 추가되면, 1~k, w+(1~k) 까지 만들 수 있음 이 때 k와 w+1이 이어지지 않으면 만들 수없다!
 */

int n;
vector<int> sinkers;

int main(){

    cin >> n;
    sinkers.resize(n);
    int acc = 0;

    for (int i = 0; i < n; ++i) {
        int input;
        cin >> input;
        sinkers[i] = input;
    }

    sort(sinkers.begin(), sinkers.end());

    for(auto sinker : sinkers){
        if(acc + 1 < sinker) break;
        acc +=sinker;
    }

    cout << acc+1;



}

