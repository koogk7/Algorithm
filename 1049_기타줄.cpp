// ConsoleApplication2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define INF 987654321


struct brand{
    int packege, one;
};

int main() {
    int n,m;
    vector<brand> brands;
    int packege, one;
    int minPack = INF;
    int minOne = INF;
    int ans = 0;

    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        cin >> packege >> one;

        if(packege > one * 6)
            packege = one * 6;

        brands.push_back({packege, one});
        minPack = min(minPack, packege);
        minOne = min(minOne, one);
    }

    ans = n / 6 * minPack + min(minPack, n % 6 * minOne);
    cout << ans;
}


