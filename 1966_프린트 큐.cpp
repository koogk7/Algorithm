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
#include "typeinfo"




using namespace std;

/*
 * 1966 프린트 큐
 *  - 소요시간 : 30분
 *  - 처음에 그저 우선순위 큐만 사용하면 되는 줄 알았다.
 *  - 항상 문제를 제대로 읽고 의심하자!
 */


struct document{
    int num, prior;
};

struct cmp{
    bool operator()(document a, document b){
        if(a.prior == b.prior)
            return a.num < b.num;
        return a.prior < b.prior;
    }
};
int t;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> t;

    while(t--){
        int n, target;
        priority_queue<document, vector<document>, cmp>pq;
        queue<document>que;
        int input;

        cin >> n >> target;

        for (int i = 0; i < n; ++i) {
            cin  >> input;
            que.push({i, input});
            pq.push({i, input});
        }

        int i = 0;

        while(!que.empty()){
            int maxPrio =  pq.top().prior;
            document current = que.front();
            que.pop();

            if(current.prior < maxPrio)
                que.push(current);
            else {
                pq.pop();
                if(current.num == target)
                    break;
                i++;
            }
        }

        cout << i + 1 << "\n";

    }

}

