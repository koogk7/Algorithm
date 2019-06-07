#include <iostream>
#include <vector>
#include <set>

using namespace std;


char box[21][21];
int R, C;
set<char> alpha;
int set_cnt = 0;
int d_row[] = {-1,1,0,0};
int d_col[] = {0,0,-1,1};
int max_cnt;
int nrow, ncol;

bool isBoundary(int row, int col)
{
    int is_row = row >=0 && row < R;
    int is_col = col >=0 && col < C;

    return  is_row && is_col;

}


void dfs(int row, int col)
{
    int befor_cnt = set_cnt;
//    cout << "row : "<< row << " col : " << col<<" "<<box[row][col] <<endl;

//    set<char>::iterator iter;
//    for(iter = alpha.begin(); iter != alpha.end(); iter++)
//        cout << *iter << " ";
//    cout << endl;

    for (int i = 0; i < 4; ++i) {
        nrow = row + d_row[i];
        ncol = col + d_col[i];
            if(isBoundary(nrow,ncol)){
                alpha.insert(box[nrow][ncol]);
                set_cnt = alpha.size();
                if (set_cnt > befor_cnt) {
                    if(max_cnt < set_cnt)
                        max_cnt = set_cnt;
                    dfs(nrow, ncol);
                }
        }
    }


    alpha.erase(box[row][col]);


}

int main()
{
    cin >> R >> C;

    for (int i = 0; i < R ; ++i) {
        for (int j = 0; j < C; ++j) {
            cin >> box[i][j];
        }
    }
    alpha.insert((box[0][0]));
    dfs(0,0);

    cout << max_cnt << endl;
//    for (int i = 0; i < R ; ++i) {
//        for (int j = 0; j < C; ++j) {
//           cout << box[i][j] << ' ';
//        }
//        cout << endl;
//    }



}



