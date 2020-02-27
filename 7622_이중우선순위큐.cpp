#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <stack>
#include <map>
#include <set>

typedef long long ll;


#define MAX_N 68
#define INF 987654321



using namespace std;

/* 7622 이중 우선순위 큐
 *
 * 회고
 *  - 난이도 상
 *  - 처음에 시간 복잡도를 잘 못 계산해서, 방법은 생각 했으나 구현을 안했음
 *  - 최소, 최대 힙을 두고 삽입은 모두, 삭제는 D 값에 따라서 삭제를 하되 싱크는 매번 맞춰준다.
 *  - 두 힙의 동기화를 위해서, 넣을 때 index(순서)를 alive key로 사용해 유효성을 검증
 *  - 하나의 TC가 끝날 때마다, 힙을 비워주지 않아서 틀렸었음
 *
 */

int T,k;
struct Node {
    int idx ,value;
};

struct maxCmp {
    bool operator()(Node a, Node b){
        return a.value < b.value;
    }
};

struct minCmp {
    bool operator()(Node a, Node b){
        return a.value > b.value;
    }
};

priority_queue<Node, vector<Node>, maxCmp> maxHeap;
priority_queue<Node, vector<Node>, minCmp> minHeap;
map<int,bool>alive;

void sync(){
    while(!maxHeap.empty() && !alive[maxHeap.top().idx]){
        maxHeap.pop();
    }
    while(!minHeap.empty() && !alive[minHeap.top().idx]){
        minHeap.pop();
    }
}

int deleteMax() {
    while(!alive[maxHeap.top().idx]){
        maxHeap.pop();
    }

    int maxValue = maxHeap.top().value;
    alive[maxHeap.top().idx] = false;
    maxHeap.pop();
    sync();
    return maxValue;
}

int deleteMin() {
    while(!alive[minHeap.top().idx]){
        minHeap.pop();
    }
    int minValue = minHeap.top().value;
    alive[minHeap.top().idx] = false;
    minHeap.pop();
    sync();
    return minValue;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;

    while(T--){
        char oper;
        int value;
        cin >> k;

        maxHeap = priority_queue<Node, vector<Node>, maxCmp>();
        minHeap = priority_queue<Node, vector<Node>, minCmp>();

        for (int i = 0; i < k; ++i) {
            cin >> oper >> value;

            bool isDelete = oper == 'D' && !maxHeap.empty() && !minHeap.empty();

            if(oper == 'I'){
                maxHeap.push(Node{i,value});
                minHeap.push(Node{i,value});
                alive[i] = true;
            }

            if(isDelete){
                value == 1 ? deleteMax() : deleteMin();
            }
        }

        if(maxHeap.empty() || minHeap.empty())
            cout << "EMPTY" <<"\n";
        else{
            int maxValue = deleteMax();
            int minValue = minHeap.empty() ? maxValue : deleteMin();
            cout << maxValue <<" "<< minValue << "\n";
        }

    }
}










