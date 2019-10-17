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
#include <sstream>
#include <string.h>
using namespace std;
typedef long long ll;

/*
 * 7662 우선순위큐 실패
 *  - 왜 실팬지 모르겠다... 아마 큐간의 동기화 문제인듯싶다.
 */


int main(){
   int T;
   cin >> T;

   while(T--){
       int n;
       cin >> n;

       priority_queue<ll> max_pq; // 내림차순
       priority_queue<ll, vector<ll>, greater<>> min_pq; // 오름차순
       map<ll,ll> alive;


       for (int i = 0; i < n; ++i) {
           char oper;
           ll value;


           cin >> oper >> value;
           // insert
           if(oper == 'I'){
               max_pq.push(value);
               min_pq.push(value);
               alive[value] += 1;
           }

           if(max_pq.empty() or min_pq.empty())
               continue;
           if(alive[max_pq.top()] == 0 or alive[min_pq.top()] == 0)
               continue;

           // 1 delete
           if(oper == 'D' and value == 1){

               ll top;
               do{
                top = max_pq.top();
                max_pq.pop();
               }while(alive[top] < 1);

               alive[top]--;
           }

           // -1 delete
           if(oper == 'D' and value == -1){
               ll top;
               do{
                   top = min_pq.top();
                   min_pq.pop();
               }while(alive[top] < 1);

               alive[top]--;
           }
       }

       if(max_pq.empty() or min_pq.empty() or alive[max_pq.top()] == 0 or alive[min_pq.top()] == 0)
           cout << "EMPTY";
       else
           cout << max_pq.top() << " "<< min_pq.top();


   }


}

