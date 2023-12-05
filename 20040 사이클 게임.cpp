#include <iostream>
#include <vector>
#include <algorithm>

int N, M;   // N: 점의 개수, M: 진행된 차례의 수
std::vector<std::pair<int, int>> LINES; // LINES[i]: i 번째 진행된 차례

std::vector<int> parent;    // parent[i]: i 번째 플레이어 소속

int answer; // answer: 게임 종료 시점

int Find(int x){
    if(parent[x] == x) return x;
    return parent[x] = Find(parent[x]);
}

void Union(int a, int b){
    int pa = Find(parent[a]);
    int pb = Find(parent[b]);

    if(pa == pb) return;

    if(a >= b) {parent[pa] = pb;}
    else {parent[pb] = pa;}
    
    return;
}

void Solution(){

    parent.assign(N, 0);

    for(int i=0; i<N; ++i) {parent[i] = i;}

    for(int i=0; i<M; ++i){
        
        if(Find(LINES[i].first) == Find(LINES[i].second)) {            
            answer = i + 1;
            return;
        }
        Union(LINES[i].first, LINES[i].second);
    }

    return;
}

void Input(){

    std::cin >> N >> M;

    LINES.assign(M, {0, 0});

    for(int i=0; i<M; ++i){std::cin >> LINES[i].first >> LINES[i].second;}

    return;
}

int main(){

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    Input();

    Solution();

    std::cout << answer;

    return 0;
}

