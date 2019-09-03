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
 * 1:40분, 최소성 만족 구현이 어려웠다. 우선 조합이 갯수만큼 순차적으로 구해야하고,
 * 그 다음은 겹치는 부분집합 찾는게 어려웠으나 비트연산으로 해결
 */


vector<string> transTwo(int n, vector<int> arr1){
    vector<string> map1;

    for (int i = 0; i < arr1.size(); ++i) {
        int checker = 1;
        for (int j = n-1; j >= 0; --j) {
            int afterChecker = arr1[i] & (checker << j);
            if(afterChecker == (checker << j))
                map1.push_back("#");
            else
                map1.push_back(".");
        }
    }

    return map1;

}

vector<string> unionMap(int n, vector<string> map1, vector<string> map2){
    vector<string> rst;
    string input = "";

    for (int i = 0; i < map1.size(); ++i) {
        if(map1[i] == "#" or map2[i] == "#")
            input += "#";
        else
            input += " ";
        if(i % n == n-1){
            rst.push_back(input);
            input = "";
        }
    }

    return rst;
}

vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
    vector<string> answer;
    vector<string> map1 = transTwo(n, arr1);
    vector<string> map2 = transTwo(n, arr2);

    answer = unionMap(n, map1, map2);

//    for (int i = 0; i < answer.size(); ++i) {
//        cout << answer[i] << "\n";
//    }
    return answer;
}


int main(){

    int n = 5;
    vector<int> arr1 = {9, 20, 28, 18, 11};
    vector<int> arr2 = {30, 1, 21, 17, 28};
    solution(n, arr1, arr2);


}

