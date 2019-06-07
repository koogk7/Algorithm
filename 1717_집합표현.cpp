#include <iostream>
#include "vector"


/*
    0 a b : a 합집합 b, 1 a b : a,b가 같은 집합인지 확인
    n은 n 이하의 자연수, m은 연산의 갯수
  */

using namespace std;

class UnionFind {
    private:
        vector<int> parent; // 해당 index가 속해있는 set을 저장하고 있는 vector
        vector<int> rank; // 해당 index의 트리높이
    public:
        UnionFind(int n){
            for(int i = 0; i< n; i++){
                parent.push_back(i); // set을 자기 자신으로 초기화
                rank.push_back(1);

            }
        }
        int Find(int x);
        void UnionSet(int a, int b);
};

int main() {
    int n = 0 , m = 0;
    int a_set, b_set;
    vector<string> rslt;
    int temp[3];
    cin >> n >> m;
    UnionFind uf(n+1);

    for (int i = 0; i < m; ++i) {
        cin >> temp[0] >> temp[1] >> temp [2];

        if(temp[0] == 0){
            //union
            uf.UnionSet(temp[1], temp[2]);
        }
        else{
            //Find
            a_set = uf.Find(temp[1]);
            b_set = uf.Find(temp[2]);
            if(a_set == b_set)
                rslt.push_back("YES");
            else
                rslt.push_back("NO");

        }
    }

    for (int j = 0; j < rslt.size(); ++j) {
        cout << rslt[j] << " ";
    }

    return 0;
}




// 해당 인자의 부모를 찾는다.
int UnionFind ::Find(int x)
{
    if(parent[x] == x)
        return x;

    return Find(parent[x]); // 자기 상위 부모의 부모를 계속해서 찾아감
}

// Rank(트리의 높이)가 큰녀석 아래로 작은 녀석이 들어옴
void UnionFind::UnionSet(int a, int b)
{
    int a_parent = Find(a);
    int b_parent = Find(b);

//    cout << "a_parent : " << a_parent << " b_parent : " << b_parent <<endl;

    if ( a_parent == b_parent)
        return;

    if(rank[a_parent] >= rank[b_parent]) {
        parent[b_parent] = a_parent;
        rank[a_parent]++;
    }
    else {
        parent[a_parent] = b_parent;
        rank[b_parent]++;
    }


}

// parent 1 2 3 4 5 6 7
// rank   1 1 1 1 1 1 1

// parent 0 1 2 1 4 5 6
// rank   1 2 1 1 1 1 1
