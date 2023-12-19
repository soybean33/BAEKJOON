#include <iostream>
#include <vector>

int N, M, K;    //N: 학생의 수, M: 친구관계 수, K: 가지고 있는 돈
std::vector<int> A; // A[i]: i 학생이 원하는 친구비

std::vector<int> parent;    // parent[i]: 친구 관계
int answer; // answer: 최소 친구 비

int Find(int x) {
    if(parent[x] == x) return x;
    return parent[x] = Find(parent[x]); 
}

void Union(int a, int b){
    int pa = Find(a);
    int pb = Find(b);
    
    if(pa == pb) return;

    if(A[pa] > A[pb]) {parent[pa] = pb;}    // 더 저렴한 쪽으로
    else {parent[pb] = pa;}

    return;
}

void Solution(){

    parent.assign(N+1, 0);
    for(int i=1; i<=N; ++i) {parent[i] = i;}

    for(int i=0; i<M; ++i) {
        int a, b;
        std::cin >> a >> b;
        Union(a, b);    // 친구
    }

    std::vector<bool> visited;  // visited[i]: 친구비 계산 여부
    visited.assign(N+1, false);
    for(int i=1; i<=N; ++i){
        int curr = Find(i); // curr: 현재 친구
        if(visited[curr] == true) {continue;}   // 이미 친구비를 계산 했다면 continue
        answer += A[curr];  // 친구비 계산
        visited[curr] = true; 
    }

    return;
}

void Input(){

    std::cin >> N >> M >> K;

    A.assign(N+1, 0);
    for(int i=1; i<=N; ++i) {std::cin >> A[i];}

    return;
}

int main(){

    Input();

    Solution();

    if(answer > K) {std::cout << "Oh no";}  // 모든 학생을 친구로 만들 수 없다면
    else {std::cout << answer;} // 모든 학생을 친구로 만든 최소 비용

    return 0;
}