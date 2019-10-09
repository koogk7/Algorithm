#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <stack>
#include <string.h>
#include <queue>
using namespace std;

/*
 * 각 셀은 특성 A 또는 B를 가지고 있다.
 * 세로방향의 특성이 중요
 * 단면의 모든 세로방향에 대해서 동일한 특성의 셀들이
 * k개 이상 연속적으로 있는 경우에만 통과
 *
 * 약품을 투입할 경우 막의 모든 셀들은 하나의 특성으로 변경됨
 *
 * 접근
 *     1. 입력받을 때 각 col 별로 연속된 수를 저장한다.
 *     2. 모든 col 이 연속 수가 k보다 크면 통과
 *     3. 작다면 약품을 넣을 로우를 선택, 2^d
 *     4. 다시 연속수 업데이트 w
 *     --> 시간 복잡도 w*2^
 *회고
 *  1. 최솟값을 업데이트함으로, 항상 비교를하고 더 큰 값은 무조건 비교 x
 *  2. 함수가 불필요한 호출이 없는지 확인!
 *  3. 백트래킹은 항상 idx가 범위보다 +1까지 확인을 해야해!
 */

#define MA 10000000
int T, d,w,k;
int map[15][22];
int origin[15][22];
int ans = MA;
vector<int> seq; // 각 컬럼의 연속수


void getSeq(int col)
{

    seq[col] = 0;
    int cnt = 1;
    for (int i = 1; i < d; ++i) {
//        if(cnt >= k) break;
        if(map[i][col] == map[i-1][col]){
            cnt++;
        } else{
            seq[col] = max(seq[col],cnt);
            cnt = 1;
        }
    }
    seq[col] = max(seq[col],cnt);
}

bool isPass()
{
    bool rst = true;
    for (int c = 0; c < w; ++c) {
        getSeq(c);
        if(seq[c] < k) return false;
    }
    return rst;
}

void Inject(int row, int value)
{
    for (int i = 0; i < w; ++i) {
        map[row][i] = value;
    }
}

void Change(int idx, int value)
{
    if(value == -1) {
        for (int i = 0; i < w; ++i) {
            map[idx][i] = origin[idx][i];
        }
    } else {
        Inject(idx, value); // a주입
    }
}

int BackTracking(int idx, int cnt){ // idx == 로우
    if(ans <= cnt) return MA;
    if(idx > d) return MA;
    if(isPass()){ // 모두 검사통과
        ans = cnt;
        return ans;
    }

    BackTracking(idx + 1, cnt); // 주입안함

    Change(idx,0);
    BackTracking(idx + 1, cnt + 1);
    Change(idx,-1); // 복구

    Change(idx,1);
    BackTracking(idx + 1, cnt + 1);
    Change(idx,-1);

    return ans;
}

int main(){

    cin >> T;
    for (int t = 0; t < T; ++t) {
        ans = MA;
        cin >> d >> w >> k;
        seq = vector<int>(w,0);
        for (int i = 0; i < d; ++i) {
            for (int j = 0; j < w; ++j) {
                cin >> map[i][j];
                origin[i][j] = map[i][j];
            }
        }


        for (int c = 0; c < w; ++c) {
            getSeq(c);
        }

        cout << "#" << t+1 << " " <<  BackTracking(0,0) << endl;
    }
}
