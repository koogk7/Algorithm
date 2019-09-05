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
 * 알고리즘 헤더에 있는 집합 연산 사용법을 배울 수 있었음
 * 주의할 점은 교집합 같은 경우에는 인풋집합의 자료구조 특성을 따른다. 예를 들어 인풋인자로 벡터를 주면
 * 서로 다른 녀석이 발견되면 그냥 함수가 끝나버린다 이거 조심!
 * 스트링에 char 타입을 주고싶으면 "" 로 초기화 한후에 +연산을 통해 더하자
 */


multiset<string> toSetElement(string str){

    string innerStr = str;
    string onlyAlphabet = "";
    multiset<string> rst;
    transform(innerStr.begin(), innerStr.end(), innerStr.begin(), ::tolower); // 소문자로 통일


    for (int i = 0; i < innerStr.size()-1; ++i) {
        bool isAlphabet = 97 <= innerStr[i] and innerStr[i] <= 122;
        isAlphabet = isAlphabet and 97 <= innerStr[i+1] and innerStr[i+1] <= 122;
        if(!isAlphabet) continue;
        string element = "";
        element += innerStr[i];
        element += innerStr[i+1];
        rst.insert(element);
    }


    return rst;

}

int solution(string str1, string str2) {
    int answer = 0;
    multiset<string> set1;
    multiset<string> set2;
    vector<string> unionSet;
    vector<string> intersectionSet;

    set1 = toSetElement(str1);
    set2 = toSetElement(str2);


    unionSet.resize(set1.size() + set2.size());
    intersectionSet.resize(set1.size());

    auto unionLast = set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), unionSet.begin());
    auto interLast = set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), intersectionSet.begin());

    unionSet.erase(unionLast, unionSet.end());
    intersectionSet.erase(interLast, intersectionSet.end());


    for(const auto &i : set1) cout << i << " ";
    cout << endl;
    for(const auto &i : set2) cout << i << " ";
    cout << endl;
//    for(const auto &i : intersectionSet) cout << i << " ";
//    cout << endl;

    cout << unionSet.size() << " " << intersectionSet.size() << endl;

    if(unionSet.empty())
        answer = 65536;
    else
        answer = static_cast<int>(intersectionSet.size() *  65536 / unionSet.size() );
    cout << answer;

    return answer;
}

int main(){

    int n = 5;
    string str1 = "E=M*C^2";
    string str2 = "e=m*c^2";
    solution(str1, str2);



}

