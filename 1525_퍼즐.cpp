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
#include <bitset>

using namespace std;



const int shift[4] = {-12, 12, -4, 4};
const int dr[4] = {1, -1, 0, 0};
const int dc[4] = {0, 0, 1, -1};

bool isBoundary(int row, int col){
    return row >=0 && row < 3 && col >= 0 && col < 3;
}

//비트 출력
void printBits(long long number){
    string bits = bitset<36>(number).to_string();


    for (int j = 0; j < bits.size(); ++j) {
        cout << bits[j] << "";
        if(j % 4 == 3)
            cout << " ";
    }

    cout << endl;
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);


    // 퍼즐안의 최댓수는 9임으로 하나의 수는 4비트로 표현이 가능하다.
    // 퍼즐 안의 전체수를 담아내기 위해서는 는 4 * 8 = 36bit가 필요함으로
    // 32bit형인 int로는 담을수가 없다. 따라서 64bit 형인 long long을 사용한다.
    long long start = 0;

    /*
     * 0 1 2
     * 3 4 5
     * 6 7 8
     *
     * 위 그래프를 왼쪽 위에서 부터 비트마스킹을 하게 되면
     * 0000 0001 0010 , 0011 0100 0101, 0110 0111 1000 이 된다.
     * 1, 2 을 담는 과정을 살펴보자
     *      1. 입력으로 1을 받는다.
     *          cin >> input;
     *      2. start 변수에 저장한다.
     *          start = start + input // start 하위 12 bit : 0000 0000 0001
     *      3. 입력으로 2을 받는다.
     *          cin >> input;
     *      4. start 변수에 담겨 있던 1 정보를 오른쪽으로 밀어내고 새로운 0000에다 2을 받는다.
     *          start = start << 4 // start 하위 12 bit : 0000 0001 0000
     *          start = start + input // start 하위 12 bit: 0000 0001 0010
     */

    for (int i = 0; i < 9; ++i) {
        int input;
        cin >> input;
        start = (start << 4) + input; // 입력을 받을 때마다, 이전 입력을 왼쪽 shift해서 0000인 곳에 값을 받는다.
    }


    /*
     * 1 2 3
     * 4 5 6
     * 7 8 0
     * 위 그래프를 담고 있는 dest 변수 선언
     */
    long long dest = 0;
    for (int i = 1; i < 9; ++i) {
        dest = (dest << 4 ) + i;
    }
    dest <<= 4;


    set<long long> visited; // 왜 visit을 set으로 했지?
    queue<long long> que;
    que.push(start);
    visited.insert(start);

    int result = 0;
    while(!que.empty()){

        int qSize = static_cast<int>(que.size());
        for (int i = 0; i < qSize; ++i) {
            long long current = que.front();
            que.pop();

            // 목적지와 같은 그래프라면 종료
            if(current == dest){
                cout << result << "\n";
                return 0;
            }

            /*
             * 15LL = 0000 ~~~~~ 1111
             * 1111 과 4비트를 And 연산했을 때 0000이 나오면 우리가 원하던 빈블록의 위치가 된다.
             * 이를 찾기 위해 4비트씩 올려가면서 비교를 한다. 4비트씩 올린다는건 4비트씩 오른쪽으로 shift한다는 애기!
             */
            int posEmpty = 0; // 비어있는 퍼즐 위치
            for (; current & (15LL << posEmpty*4) ; posEmpty++);
            int row = posEmpty / 3;
            int col = posEmpty % 3;

            for (int d = 0; d < 4; ++d) {
                int nr = row + dr[d];
                int nc = col + dc[d];
                if(!isBoundary(nr,nc)) continue;
                // 이동 할 위치에 있는 부분의 bit
                // row는 3개씩 건너뛰고, col는 하나씩 건너뛴다.
                long long temp = current & (15LL << (nr*3 + nc)*4);
                // 이동한 후의 값, temp 와 빈 블록의 비트만 0000으로 채워진다.
                long long next = current - temp;

                //방향에 따라 temp를 쉬프트해서 더해준다.
                if(shift[d] > 0) temp <<= shift[d];
                else temp >>= -shift[d];
                next += temp;

                /*
                 * set의 find는 찾지 못할 경우 마지막 원소를 리턴한다.
                 * 방문하지 않은 녀석들만 큐에 삽입한다.
                 */
                if(visited.find(next) == visited.end()){
                    visited.insert(next);
                    que.push(next);
                }
            }

        }
        result++;
    }
    cout << "-1" << "\n";

}

