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
 * 2805 나무자르기 회고
 * 처음에 이분탐색을 고려했으나, 이분탐색 시간복잡도를 nlogn으로 착각하고 있었다.
 * 가장 빠르게 서치하는 방법이 이분탐색! 범위를 절반으로 줄여가며 결국 Log n만의 가능
 *
 */

int n, m;
int max_height;
vector<int> tree;

int binarySearch(int n, int target){
    int bottom = 0;
    int top = max_height;
    int mid = 0;


    while (bottom <= top){

        mid = (bottom + top) / 2;
        long long total_block_cnt = 0;

        for (int i = 0; i < n; ++i) {
            total_block_cnt += tree[i] > mid ? tree[i] - mid : 0;
        }

        if(total_block_cnt < target) top = mid - 1;
        else bottom = mid + 1;

    }

    return top;
}


int main(){

    cin >> n >> m;

    tree.resize(n);

    for (int i = 0; i < n; ++i) {
        cin >> tree[i];
        max_height = max(max_height, tree[i]);
    }

    cout << binarySearch(n,m);

}

