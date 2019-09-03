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


bool visit[100];
vector<int> columns;
vector<vector<string>> gRelation;
//map<string, bool> keys;
vector<int> keys;
int columnsNumber = 3;
string hashKey = ",";

bool isUnique(){
    set<string> rows;

    for (int i = 0; i < gRelation.size(); ++i) {
        string input = "";
        for (int j = 0; j < columns.size(); ++j) {
            int column = columns[j];
            input += hashKey + gRelation[i][column];
        }
        rows.insert(input);
    }

    return rows.size() == gRelation.size();
}

void combination(int idx, int cnt, int number){
    if(cnt == number){

        if(isUnique()) {
            int key = 0;
            for (int i = 0; i < columns.size(); ++i) {
                key |= 1 << columns[i];
            }

            for (int i = 0; i < keys.size(); ++i) {
                if((keys[i] & key) == keys[i])
                    return;
            }

            keys.push_back(key);
        }

        return;
    }

    for (int i = idx+1; i < columnsNumber; ++i) {
        if(visit[i]) continue;
        columns.push_back(i);
        visit[i] = true;
        combination(i, cnt+1, number);
        columns.pop_back();
        visit[i] = false;
    }
}



int solution(vector<vector<string>> relation) {
    int answer = 0;

    gRelation.assign(relation.begin(), relation.end());

    columnsNumber = relation[0].size();

    for (int i = 1; i < columnsNumber + 1; ++i) {
        combination(-1,0,i);
    }


    answer = keys.size();

    return answer;
}


int main(){
    vector<vector<string>> record = {{"100","ryan","music","2"},
                                     {"200","apeach","math","2"},
                                     {"300","tube","computer","3"},
                                     {"400","con","computer","4"},
                                     {"400","muzi","computer","3"},
                                     {"600","apeach","music","2"}};
    solution(record);


}

