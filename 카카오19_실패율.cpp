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
using namespace std;

/*
 * 50분, 나누는 분모가 0이 될 때를 놓치고 있었다
 */

vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;

    struct failRate {
        int stage;
        float rate;
    };

    struct cmp {
        bool operator()(failRate a, failRate b){
            if(a.rate == b.rate)
                return a.stage > b.stage;
            return a.rate < b.rate;
        }
    };

    priority_queue<failRate, vector<failRate>, cmp> pq;

    sort(stages.begin(), stages.end());


    for (int i = 0; i < N; ++i) {
        int current_stage = 0;
        int start = lower_bound(stages.begin(), stages.end(), i+1) - stages.begin();
        int total = stages.size() - start;


        while(stages[start+ current_stage]  == i + 1){
            current_stage++;
        }

        cout << current_stage << "/" << total << " ";


        if(total == 0)
            pq.push({i, 0});
        else
            pq.push({i, float(current_stage) / float(total)});
    }

    cout << "\n";

    while (!pq.empty()){
        cout << pq.top().stage + 1 << " ";
        answer.push_back(pq.top().stage + 1);
        pq.pop();
    }

    return answer;
}


int main(){
    vector<int> record = {1,1,1,1,1,1,1};
    solution(3, record);
}

