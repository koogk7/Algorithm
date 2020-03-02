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

/* 13335 트럭
 *
 * 회고
 *  - 난이도 중
 *  - 트럭이 다리에서 빠져나온 뒤, 새로운 트럭이 들어오는 경우를 반대로 주고 있었다.
 *  - 큐를 사용할 때 푸시를 먼저 할건지, 팝을 먼저 할건지가 매우 중요!!!
 *
 */

struct OnBridge {
    int weight, dist, time;
};
int n, w, l;
int ans, weightOnBridge, arrive;
vector<int> trucks;
queue<OnBridge> bridge;

int startTruck(int idx){
    if(weightOnBridge + trucks[idx] <= l){
        bridge.push({trucks[idx], 1, ans});
        weightOnBridge += trucks[idx++];
    }
    return idx;
}

void moveTruck(){
    while(!bridge.empty()){
        OnBridge truck = bridge.front();
        if(truck.time != ans)
            break;
        bridge.pop();
        if(truck.dist < w){
            truck.dist++;
            truck.time++;
            bridge.push(truck);
        } else { // 도착
            weightOnBridge -= truck.weight;
            arrive++;
        }
    }
    ans++;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> w >> l;
    trucks = vector<int>(n,0);
    for (int i = 0; i < n; ++i) {
        cin >> trucks[i];
    }

    int idx = 0;

    while(arrive < n){
        moveTruck();
        idx = startTruck(idx);
    }
    cout << ans;
}










