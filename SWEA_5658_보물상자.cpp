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

/*
 * SWEA 5658 보물상자 비밀번호
 *  - 들어 올 수 있는 최댓값 계산을 잘못해서, 배열 인덱스로 받았다가 벡터로 바꿈
 *  - 문제의 중복된 수를 카운트 하지말라는 문구를 읽지 못했음
 *  - 항상 벡터를 초기화 하자!
 *  - unique 메소드를 통해, 벡터의 중복값들을 배열 맨 끝으로 보낼 수 있음!
 *
 */


using namespace std;

int T,n,k;
int lineSize;
vector<int> box[4];
vector<int> decList;


int charToInt(char ch){
   if(ch == 'A')
       return 10;
   if(ch == 'B')
       return 11;
   if(ch == 'C')
       return 12;
   if(ch == 'D')
       return 13;
   if(ch == 'E')
       return 14;
   if(ch == 'F')
       return 15;

   return ch - '0';
}

void transDec(){
    for (int i = 0; i < 4; ++i) {
        int decValue = 0;
        int powIndex = 0;
        for (int j = lineSize-1; j >= 0; --j) {
            decValue += pow(16,powIndex++) * box[i][j];
        }
        decList.push_back(decValue);
    }
}

void rotate(){

    vector<int> rotateValue;

    for (int i = 0; i < 4; ++i) {
        rotateValue.push_back(box[i][lineSize-1]);
        for (int j = lineSize-1; j >= 1 ; --j) {
            box[i][j] = box[i][j-1];
        }
    }

    for (int i = 0; i < rotateValue.size() - 1; ++i) {
        box[i+1][0] = rotateValue[i];
    }
    box[0][0] = rotateValue.back();

}

void Display(int mode)
{
    cout<<"############"<<endl;

    if(mode == 1) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < lineSize; ++j) {
                cout << box[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        for (int i = 0; i < 4100; ++i) {
            cout << decList[i] << " ";
        }
        cout <<endl;
    }
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> T;
    int t = 0;

    while(T--){
        t++;
        cin >> n >> k;

        int lineIdx = -1;
        int findIdx = 0;
        char input;
        lineSize = n/4;

        for (int i = 0; i < 4; ++i) {
            box[i].clear();
        }
        decList.clear();

        for (int i = 0; i < n; ++i) {
            if(i % lineSize == 0)
                lineIdx++;
            cin >> input;

            box[lineIdx].push_back(charToInt(input));
        }

        transDec();

        for (int i = 0; i < lineSize; ++i) {
            rotate();
            transDec();
        }

        sort(decList.begin(), decList.end(), [](int a, int b){
            return a > b;
        });

        unique(decList.begin(), decList.end());

        cout << "#" << t << " " << decList[k-1] << "\n";

    }


}

