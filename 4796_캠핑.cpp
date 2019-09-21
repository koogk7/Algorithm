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
 */

int n;

int main(){

    int l,p,v;
    int i = 1;
    while(1){
        cin >> l >> p >> v;
        if(l+p+v == 0)
            break;
        int ans = (v/p) * l;
        int remain = min(v%p, l);
        cout << "Case " << i <<":" << " " << ans + remain << "\n";
        i++;
    }

}

