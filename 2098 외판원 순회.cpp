#include <iostream>
#include <vector>
#include <algorithm>

constexpr int INF = 21e8;   // INF: 나올 수 없는 값

int N;  // N: 도시의 수
std::vector<std::vector<int>> W;    // W[i][j]: i 도시에서 j 도시로 가기 위한 비용

int answerBit;  // answerBit: 모든 도시를 방문한 경우의 비트
std::vector<std::vector<int>> cost; // cost[i][j]: 현재 방문 중인 도시 i 와 i 도시를 방문하기 까지 방문한 도시의 정보와 최소 비용

int Dfs(int node, int bit){

    if(bit == answerBit){   // 모든 도시를 방문한 경우
        if(W[node][0] == 0) return INF; // node 도시를 방문할 수 없는 경우
        else return W[node][0]; // node 도시를 방문할 수 있는 경우
    }

    if(cost[node][bit] != -1) return cost[node][bit];   // 방문한 적이 없다면 방문

    cost[node][bit] = INF;

    for(int i=0; i<N; ++i){
        if(W[node][i] == 0) {continue;} // 현재 도시에서 방문할 수 없는 도시 continue
        if((bit & (1 << i)) == (1 << i)) {continue;}    // 이미 방문한 도시 continue

        cost[node][bit] = std::min(cost[node][bit], W[node][i] + Dfs(i, bit | 1 << i)); // 방문 정보와 최소 비용 갱신
    }

    return cost[node][bit];
}

void Solution(){

    cost.assign(N, std::vector<int>(1<<N, -1));

    std::cout << Dfs(0, 1);

    return;
}

void Input(){

    std::cin >> N;

    W.assign(N, std::vector<int>(N, 0));

    for(int j=0; j<N; ++j){
        for(int i=0; i<N; ++i){
            std::cin >> W[j][i];
        }
    }

    answerBit = (1<<N) -1;

    return;
}

int main(){
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    Input();

    Solution();

    return 0;
}