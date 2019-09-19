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




int main(){
    string input = "";
    while(1){

        cin >> input;
        if(input == "0") break;
        int input_size = input.size();
        string ans = "yes";

        for (int i = 0; i < input_size/2; ++i) {
            if(input[i] == input[input_size -1 - i]) continue;
            ans = "no";
        }

        cout << ans << "\n";
    }

}

