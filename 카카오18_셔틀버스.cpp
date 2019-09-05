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

string solution(int n, int t, int m, vector<string> timetable){
    string answer = "";
    priority_queue<int, vector<int>, greater<int>> times;
    int hour, minute;

    for (int i = 0; i < timetable.size(); ++i) {
        hour = (timetable[i][0] - '0')*10 + (timetable[i][1] - '0');
        minute = (timetable[i][3] - '0')*10 + (timetable[i][4] - '0');
        times.push(hour*60 + minute);
    }



    int start;
    int cnt = 0;
    int rst;

    for (int i = 0; i < n-1; ++i) {
        start = 9*60 + (i*t);
        cnt = 0;

        while(!times.empty() and cnt < m){
            if(times.top() <= start){
                times.pop();
                cnt++;
            } else break;
        }
    }

    cnt = 0;
    start = 9 * 60 + t*(n-1);
    while(!times.empty() and cnt < m - 1){
        if(times.top() <= start){
            times.pop();
            cnt++;
        } else break;
    }

    if(times.empty() or times.top() > start){
        rst = start;
    } else{
        rst = times.top() - 1;
    }

    hour = rst/60;
    minute = rst%60;

    answer += hour/10 + '0';
    answer += hour%10 + '0';
    answer += ":";
    answer += minute/10 + '0';
    answer += minute%10 + '0';


    cout << rst;
    cout << answer;

    return answer;

}


int main(){

    int n = 2;
    int t = 10;
    int m = 2;

    vector<string> cities = {"08:00", "08:01", "08:02", "08:03"};
    solution(n,t,m, cities);



}

