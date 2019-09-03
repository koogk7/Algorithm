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
using namespace std;

vector<string> solution(vector<string> record) {
    vector<string> answer;

    string userId;
    string msg;
    string nickName;
    struct Chat {
        string type;
        string id;
    };
    map<string, string> userList;
    queue<Chat> que;
    for (int i = 0; i < record.size(); ++i) {
        stringstream ss(record[i]);
        ss >> msg >> userId >> nickName;

        if(msg != "Leave")
            userList[userId] = nickName;
        if(msg != "Change")
            que.push({msg, userId});
    }
    while (!que.empty()){
        Chat chat = que.front();
        que.pop();
        string output = userList[chat.id];
        if("Enter" == chat.type)
            output +=  "님이 들어왔습니다.";
        else
            output += "님이 나갔습니다.";
        answer.push_back(output);
    }


    return answer;
}


int main(){
    vector<string> record = {"Enter uid1234 Muzi", "Leave uid1234", "Enter uid4567 aaa"};
    solution(record);
}

