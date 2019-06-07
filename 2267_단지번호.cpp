#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;


int input_map[25][25]; // 26*26*4byte = 2704byte
int n;
int visit[26][26]; // 26*26*4byte = 2704byte
int dir[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1}}; // 상하좌우
vector <int> house_cnt; // 단지 내 집 수
int set_cnt; // 단 지 수

bool isInside(int row, int colum)
{
    return (row>=0 && row <n) && (colum >= 0 && colum < n);
}

void dfs(int row, int column, int key)
{
    input_map[row][column] = key;

    // 상,하,좌,우 순으로 탐색
    for (int i = 0; i < 4; ++i) {
        int dx = column + dir[i][0];
        int dy = row + dir[i][1];

        if(isInside(dy,dx) && input_map[dy][dx] == 1){
            dfs(dy,dx,key);
        }
    }
}

void Solution(int n)
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(input_map[i][j] == 1)
            {
                set_cnt++;
                house_cnt.push_back(0);
                dfs(i,j,set_cnt+1); // 첫번째 단지 일경우 key와 1이 겹침으로 +1을 해준값을 넘겨준다.
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(input_map[i][j] > 1)
            {
               house_cnt[input_map[i][j]]++;
            }
        }
    } // 마킹한 key 값들을 count --> 단지 내 집 수
}



int main()
{
    //key값과 vector 인덱스를 맞춰준다.
    house_cnt.push_back(0);
    house_cnt.push_back(0);

    cin >> n;

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j){
//           cin으로 입력 받을 경우 개행문자 단위로 받기때문 한 line을 하나의 int로 받음
//           cin >> input_map[i][j];
            scanf("%1d", &input_map[i][j]);
//            cout << input_map[i][j] << " ";
        }
//        cout <<  i << " ---------------" << endl;

    } // 입력

    Solution(n);
    sort(house_cnt.begin(),house_cnt.end());

    cout << set_cnt << endl;
    for (int k = 2; k < house_cnt.size(); ++k) {
        cout << house_cnt[k] <<endl;
    }

    return 0;
}


