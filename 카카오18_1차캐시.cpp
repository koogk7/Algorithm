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
 * 항상 경계값을 테스트해보자, 캐시사이즈가 0일때도 캐시를 넣고 있어서 문제가 됬다....
 */

void LRU(int idx, string city, map<string,int>& cache, int cacheSize){
    if(cacheSize == cache.size()){ // cache full
        string repalceKey = "";
        int replaceIndex = 987654321;
        for(auto item : cache){
            if(replaceIndex < item.second) continue;
            replaceIndex = item.second;
            repalceKey = item.first;
        }

        cache.erase(repalceKey);
    }
    cache.insert(make_pair(city, idx));
}

int solution(int cacheSize, vector<string> cities) {
    int answer = 0;
    map<string, int> cache;


    for (int i = 0; i < cities.size(); ++i) {
        transform(cities[i].begin(), cities[i].end(), cities[i].begin(), ::tolower); // 소문자로 통일
    }

    for (int i = 0; i < cities.size(); ++i) {

        if(cache.find(cities[i]) == cache.end()){ //miss
            answer += 5;
            if(cacheSize > 0)
                LRU(i, cities[i], cache, cacheSize);
        } else{
            answer += 1;
            cache[cities[i]] = i;
        }
    }

    cout << answer;

    return answer;
}

int main(){

    int csize = 0;
    vector<string> cities =
            {"Jeju", "Jejud", "Jeju", "dd", "Jeju"};
    solution(csize, cities);



}

