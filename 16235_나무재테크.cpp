#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
/*
 * 모든 칸에 양분이 5만큼 들어있다
 * 나무는 자기 구역에 양분만 먹을 수 있다
 * 나이만큼 양분을 먹는다 ---> x 사망
 * 한 구역에 여러개라면 나이가 어린 나무부터
 * 봄 : 나이만큼 양분을 먹고, 나이가 1 증가
 * 여름 : 봄에 죽은 나무가 양분으로 변함, 죽은 나무 나이 /2 -> 양분
 * 가을 : 번식, 나무가 5의 배수 일 때마다 번식 가능, ---> 8개의 칸에 1인 나무가 생김
 * 겨울 : 양분을 보충, 입력을 ㅗ주어짐
 *
 * ---> k년이 지난 후의 살아 있는 나무의 갯수를 구해라
 * 나무를 우선순위 큐에 저장, 나이 순으로 큐에 넣자
 * 죽은 나무는 - 곱해주어 가장 큐 앞에 저장
 * 나이가 -이면 봄은 스킵, 여름에 양분으로 변환
 * 가을은 나이가 5의 배수에 따라 인접한 칸 8개의 위치와 나이 1로 큐에 삽입
 * 겨울에 큐에 따라서 나이가 0보다 큰 나무는 양부을 보충
 * 근데 푸시,팝 연산이 너무 많아, 그냥 배열로 하고 소팅을 할까?
 * */

//1 1 1
//1
//1 1 1

using namespace std;

struct tree{
    int row , col, age;
};

int n, m, k;
int nut[12][12];
int feed[12][12];
vector<tree> trees;
//tree trees[102];
int ans;
int dead;
//priority_queue<tree> trees;
int dir_row[8] = {-1,-1,-1,0,0,1,1,1};
int dir_col[8] = {-1,0,1,-1,1,-1,0,1};

bool isBoundary(int r,int c)
{
    return r>=0 && r < n && c>=0 && c< n;
}

bool compare(tree a, tree b)
{
    return a.age < b.age;
}

bool dcompare(tree a, tree b)
{
    return a.age > b.age;
}

void Spring()
{

    sort(trees.begin(), trees.end(), compare); // 나무 나이 순으로 정렬
//    cout << "--------Spring-----------"<<endl;
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            cout << nut[i][j] << " ";
//        }
//        cout << endl;
//    }
//    cout << "--------Tree-----------"<<endl;
    for (int i = 0; i < trees.size(); ++i) {
//        cout << trees[i].row << " , " <<trees[i].col << " , " << trees[i].age<<endl;
//        if(trees[i].age <= 0) continue; // 죽은 나무 패스
        if(trees[i].age > nut[trees[i].row][trees[i].col]) {
            trees[i].age = -1*trees[i].age;
            dead++;
            continue; // 나무사망
        }
        nut[trees[i].row][trees[i].col] -= trees[i].age;
        trees[i].age++;
    }
}

void Summer()
{
//    cout << "--------Summer-----------"<<endl;
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            cout << nut[i][j] << " ";
//        }
//        cout << endl;
//    }
//
//    cout << "--------Tree-----------"<<endl;
//
//    for (int i = 0; i < trees.size(); ++i) {
//        cout << trees[i].row << " , " <<trees[i].col << " , " << trees[i].age<<endl;
//    }

    sort(trees.begin(), trees.end(), compare); // 나무 나이 순으로 정렬
    for (int i = 0; i < dead; ++i) {
//        if(trees[i].age < 0){
        nut[trees[i].row][trees[i].col] += -1 * (trees[i].age / 2);
//        }
    }
//    sort(trees.begin(), trees.end(), dcompare); // 나무 나이 역순으로 정렬

//    for (int i = 0; i < dead; ++i) {
//        trees.pop_back();
//        ans--;
//    }
    trees.erase(trees.begin(),trees.begin()+dead);
    ans -= dead;
//    cout << " 죽은 나무 " << dead << endl;
    dead = 0;
}

void Fall()
{
    int d = 0;
//    cout << "--------Fall-----------"<<endl;
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            cout << nut[i][j] << " ";
//        }
//        cout << endl;
//    }

//    sort(trees.begin(), trees.end(), compare); // 나무 나이 순으로 정렬

    for (int i = 0; i < trees.size(); ++i) {
        if(trees[i].age%5 == 0)
        {
            for (int j = 0; j < 8; ++j) {
                int nr = trees[i].row+dir_row[j];
                int nc = trees[i].col+dir_col[j];
                if(!isBoundary(nr,nc)) continue;
                trees.push_back({nr,nc,1});
                ans++;
                d++;
            }
        }
    }
//    cout << " 태어난 나무 " << d << endl;
}

void Winter()
{
//    cout << "--------Winter-----------"<<endl;
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            cout << nut[i][j] << " ";
//        }
//        cout << endl;
//    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            nut[i][j] += feed[i][j];
        }
    }
}

int main(){

    int a, b, c;
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m >> k;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >>feed[i][j];
            nut[i][j] = 5;
        }
    }

    for (int l = 0; l < m; ++l) {

        cin >>a;
        cin >>b;
        cin >>c;
        trees.push_back({a-1,b-1,c});
        ans++;
    }

    for (int i = 0; i < k; ++i) {
        if(ans <= 0) break;
        Spring();
        Summer();
        Fall();
        Winter();
    }

    cout << ans << endl;

}

