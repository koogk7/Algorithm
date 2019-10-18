// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define INF 987654321

/*
배열 A의 값은 각 행에 있는 모든 수의 합중 최솟값

회전연산 (r, c, s)는 가장 왼쪽 윗칸이 (r-s,c-s)
가장 오랜쪽 아랫칸이 (r+s, c+s)를 시계방향으로 한칸씩 돌린다는 의미

회전연산 순서는 next permutfh
*/

int n, m, k;
int read_only[52][52];
int write_only[52][52];
int origin[52][52];
struct operate {
    int row, col, s;
};
vector<operate> opers;
vector<int> opers_idx;
int dr[4] = { 0,1,0,-1 };
int dc[4] = { 1,0,-1,0 };


void sync(int r, int c, int s) {

    for (int i = r-s; i < r + s + 1; i++)
    {
        for (int j = c-s; j < c + s + 1; j++)
        {
            read_only[i][j] = write_only[i][j];
        }
    }
}

void display() {
    cout << "===================" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << read_only[i][j] << " ";
        }
        cout << endl;
    }
}

// 시계방향으로 90 회전
void rotate(int row, int col, int s) {
    /*
    s가 1씩 감소함에 따라 회전범위는 2씩 줄어듬
    s = 1 : 3, s = 2 : 5 , s = 3 : 7 ....
    */

    int first_size = s;

    // 가장 밖의 회전영역부터 회전, 1회전 후 다음 안쪽 부분을 회전
    while (s > 0) {
        int start_row = row - s;
        int start_col = col - s;
        int end_row = row + s;
        int end_col = col + s;


        // 맨 위쪽
        for (int i = start_col; i < end_col - 1; i++)
        {
            write_only[start_row][i + 1] = read_only[start_row][i];
        }
        write_only[start_row][start_col] = read_only[start_row + 1][start_col];

        // 맨 오른쪽
        for (int i = start_row; i < end_row - 1; i++) {
            write_only[i+1][end_col] = read_only[i][end_col];
        }
        write_only[start_row][end_col] = read_only[start_row][end_col - 1];

        // 맨 아래쪽
        for (int i = end_col; i > start_col; i--) {
            write_only[end_row][i-1] = read_only[end_row][i];
        }
        write_only[end_row][end_col] = read_only[end_row-1][end_col];

        // 맨 왼쪽
        for (int i = end_row; i > start_row; i--) {
            write_only[i-1][start_col] = read_only[i][start_col];
        }
        write_only[end_row][start_col] = read_only[end_row][start_col+1];

        s--;

    }

    write_only[row][col] = read_only[row][col];
    sync(row, col, first_size);

}


int getValue() {

    int rst = INF;

    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = 0; j < m; j++)
        {
            sum += read_only[i][j];
        }

        rst = min(rst, sum);
    }

    return rst;
}

// 회전연산 순서탐색
int backtracking() {


    int ret = INF;

    do {

        /*for (auto i : opers_idx)
            cout << i << " ";
        cout << endl;*/

        for (int i = 0; i < opers.size(); i++)
        {
            int idx = opers_idx[i];
            int r = opers[idx].row;
            int c = opers[idx].col;
            int s = opers[idx].s;
            rotate(r, c, s);//회전적용
        }

        ret = min(ret, getValue());//배열 A값 계산 및 갱신

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                read_only[i][j] = origin[i][j];
            }
        }

    } while (next_permutation(opers_idx.begin(), opers_idx.end()));


    return ret;
}


int main()
{


    cin >> n >> m >> k;

    opers = vector<operate>(k);
    opers_idx = vector<int>(k);
    int r, c, s;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> read_only[i][j];
            origin[i][j] = read_only[i][j];
        }
    }


    for (int i = 0; i < k; i++)
    {
        cin >> r >> c >> s;
        r--, c--;
        opers[i] = { r,c,s };
        opers_idx[i] = i;
    }

    //display();
    cout << backtracking();


}

