#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll;

vector<ll> tree;
vector<ll> arr;

ll init(int node, int s, int e){
    if(s == e) tree[node] = arr[s];
    else tree[node] = init(node*2, s, (s+e)/2) + init(node*2+1,(s+e)/2+1, e);
    return tree[node];
}

ll update(int s, int e, int node, int idx, int value){
    if(idx < s || idx > e) return tree[node];
    if(s == e) tree[node] = value;
    else tree[node] = update(s,(s+e)/2, node*2, idx, value)
            + update((s+e)/2+1,e, node*2+1, idx, value);
    return tree[node];
}

ll sum(int s, int e, int node, int ns, int ne){
    if(s > ne || e< ns) return  0;
    if(s <= ns && ne <= e) return tree[node];
    int mid = (ns+ne)/2;
    return sum(s,e,node*2,ns,mid) + sum(s,e,node*2+1,mid+1,ne);
}



int main(){
    int N, M, K;
    cin >> N >> M >> K;
    arr = vector<ll>(N+1);
    tree = vector<ll>(N*4);
    for (int i = 1; i <= N; ++i) {
        cin >> arr[i];
    }
    init(1,1,N);
//    for (int i = 0; i < N*4; ++i) {
//        cout << tree[i] << " ";
//    }
//    cout << sum(1,5,1,1,N);

    for (int j = 1; j <= M+K; ++j) {
        int a,b,c;
        cin >> a >> b >> c;
        if(a==1){
            update(1,N,1,b,c);
        } else
            cout << sum(b,c,1,1,N) << endl;
    }

}
