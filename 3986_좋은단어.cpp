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

using namespace std;



int n;
int ans;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    string temp;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        stack<char> st;
        cin >> temp;
        for (char i : temp) {
            if(!st.empty() and st.top() == i)
                st.pop();
            else
                st.push(i);
        }
        if(st.size() == 0) ans++;

    }

    cout << ans << "\n";

}

