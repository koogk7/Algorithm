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
 * 9375 패션왕 신혜빈
 */

int main(){
    int t,n;
    string input_key, input_value;

    cin >> t;

    while(t--){
        long long ans = 1;
        map<string, int> clothes;
        cin >> n;

        for (int i = 0; i < n; ++i) {
            cin >> input_value >> input_key;
            if(clothes.find(input_key) == clothes.end())
                clothes.insert(pair<string, int>(input_key, 1));
            else
                clothes[input_key]++;
        }

        for (auto i : clothes) ans *= (long long) (i.second + 1);
        cout << ans - 1 << "\n";

    }

}

