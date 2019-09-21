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


struct stick{
    int idx, cnt;
};

int main(){
    string input;
    int total = 0;
    stack<stick> st;
    cin >> input;

    for (int i = 0; i < input.size(); ++i) {
        // 여는 괄호, 뒤에를 봄
        //  닫는 괄호 --> 레이저, st.top()++
        //  여는 괄호 --> 막대기, st.push()
        if(input[i] == '(' and input[i+1] == ')'){
            if(st.empty()) continue;
            st.top().cnt++;
        }

        if(input[i] == '(' and input[i+1] == '('){
            st.push({i,0});
        }

        if(input[i] == ')' and input[i-1] == ')'){
            int pre_cnt = st.top().cnt;
            total += pre_cnt + 1;
            st.pop();
            if(st.empty()) continue;
            st.top().cnt += pre_cnt;
        }
        // 닫는괄호, 앞을 봄
        //  여는 괄호 --> 레이저, continue
        //  닫는 괄호 --> 막대기, st.top() 저장, st.pop, st.top + 이전 탑
    }

    cout << total << "\n";

    // total 출력

}

