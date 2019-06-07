#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
/*
 * 암호는 서로 다른 l개의 알파벳으로 구성, 최소 한개의 모음과 , 두개의 자음으로 구성
 * 또한 증가하는 순서로 배열
 * 위 조건을 만족하는 조합뽑기
 * 모음을 어떻게 뽑지?
 * 조합이니까, 최대 15c3 --> 충분히 다 검색해도 시간충분!
 * 다 뽑아놓고, 이 녀석이 모음이 있는지 없는지 검사!
 * l과 c를 헷갈려서 조금 해멨다, 조합같은 경우는 방문체크를 무조건 해주어야함! 그래야 중복된 방문을 하지 않음
 *
 * */


using namespace std;

int l,c;
char moum[] = {'a','e','i','o','u'};
char element[17];
int used[17];
char candi[17];

void BackTracking(int index, int c_size)
{
    if(c_size == l)
    {
        int condition=0 , i;
        for (i = 0; i < l; ++i) {
            for (int j = 0; j < 5; ++j) {
                if(candi[i] == moum[j])
                {
                    condition++;
                }
            }
        }
        if(condition == 0 || condition > l-2)
            return;
        cout << candi << '\n';
        return;
    }


    for (int k = index; k < c; ++k) {
        if(used[k] == 0) { // 조합의 경우 방문체크 필수!
            candi[c_size] = element[k]; // k인자 대신 index를 넣는 실수를 해서 시간 잡아먹음
            used[k] = 1;
            BackTracking(k, c_size + 1);
            used[k] = 0;
        }
    }
}

int main(){

   cin >> l >> c;

    for (int i = 0; i < c; ++i) {
        cin >> element[i];
    }

    sort(element,element+c);


    BackTracking(0,0);


}

