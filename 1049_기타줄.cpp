// ConsoleApplication2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
 * 10 ==> 6개 + 낱개 * 4

# 패키지가 낱개보다 항상 싸
# 패키지가 낱개보다 비싸 ---> 패키지 가격을 낱개 * 6

1. 6개가 제일 싼 녀석을 찾는다.
2. 낱개가 제일 싼 녀석을 찾는다.
3. 주어진 N을 6의 몫과 나머지로 나눈다. 몫의 수만큼 제일 싼 패키지를 사고, 제일 싼 나머지만큼 나머지를 산다.
 */

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


