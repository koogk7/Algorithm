// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
#include <map>
using namespace std;


/**
 * 2156번 포도주 시식
 *
 *  회고
 * 1. 현재 포도주를 안 먹고 진행하는 경우를 배제하고 있었음
 */

struct Node{
    int id;
    int x,y;
    Node* left;
    Node* right;
};


void addNode(Node* parent, Node* child){

    if(child->x < parent->x){
        if(parent->left == NULL)
            parent->left = child;
        else
            addNode(parent->left,child);
    } else{
        if(parent->right == NULL)
            parent->right = child;
        else
            addNode(parent->right, child);
    }
}

void preorder(vector<int>& ans, Node* node){
    if(node == NULL) return;

    ans.push_back(node->id);
    preorder(ans, node->left);
    preorder(ans, node->right);
}

void postorder(vector<int>& ans, Node* node){
    if(node == NULL) return;

    postorder(ans, node->left);
    postorder(ans, node->right);
    ans.push_back(node->id);
    cout << node->id << " ";
}


vector<vector<int>> solution(vector<vector<int>> nodeinfo) {

    int size = nodeinfo.size();
    vector<Node> nodes;

    for (int i = 0; i < nodeinfo.size(); ++i) {
        nodes.push_back({i+1, nodeinfo[i][0], nodeinfo[i][1]});
    }

    sort(nodes.begin(), nodes.end(),[](Node a, Node b){
        if( a.y == b.y)
            return a.x < b.x;
        return a.y > b.y;
    });

    Node* root = &nodes[0];

    for (int i = 1; i < size; ++i) {
//        cout << nodes[i].id << " ";
        addNode(root,&nodes[i]);
    }

    vector<vector<int>> answer ={{}, {}};
    preorder(answer[0],root);
    postorder(answer[1],root);
//    cout<< root->left->id;
    return answer;
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<vector<int>> nodeinfo = {{5,3},{11,5},{13,3},{3,5},{6,1},{1,3},{8,6},{7,2},{2,2}};
    solution(nodeinfo);
}

