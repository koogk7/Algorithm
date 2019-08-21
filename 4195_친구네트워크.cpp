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



using namespace std;

/*
 * 4195 친구네트워크
 *  - rank는 보통 트리 높이를 사용하지만, 임의대로 설정해서 정답을 도출 해낼 수 있게 수정하는 편이 좋다
 *  - node가 int가 아닐 경우, map을 사용해야 한다
 *  - map <string, string> 일 경우 할당되지 않은 값은 ""로 초기화 된다.
 */

struct UnionFind{
    map<string, string> parent; // index가 속해있는 set의 root
    map<string, int> rank; // 노드 갯수

    void insert(string node){
        if(parent[node] != "") // node가 존재하면 리턴
            return;
        parent[node] = node;
        rank[node] = 1;
    }

    string find(string key){
        if(parent[key] == key)
            return key;

        parent[key] = find(parent[key]);  // 경로 압축 최적화
        return parent[key];
    }

    void merge(string a, string b){
        string a_parent = find(a);
        string b_parent  = find(b);

        if(a_parent == b_parent)
            return;

        if(rank[a_parent] > rank[b_parent]) {
            parent[b_parent] = a_parent;
            rank[a_parent] += rank[b_parent];
        }
        else if (rank[a_parent] < rank[b_parent]) {
            parent[a_parent] = b_parent;
            rank[b_parent] += rank[a_parent];
        }
        else {
            rank[a_parent] += rank[b_parent];
            parent[b_parent] = a_parent;
        }

    }

    int getSize(string key){
        string key_parent = find(key);
        return rank[key_parent];
    }

};

int t,f;


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> t;


    while(t--){
        cin >> f;
        UnionFind uf;
        string a,b;

        for (int i = 0; i < f; ++i) {
            cin >> a >> b;
            uf.insert(a);
            uf.insert(b);
            uf.merge(a,b);
            cout << uf.getSize(a) << "\n";
        }

    }
}

