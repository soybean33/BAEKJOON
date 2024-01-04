#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

struct Edge{    // Edge: 다리 정보
    int to, cost;   // to: 연결되어 있는 섬, cost: 중량제한
};

int N, M;   // N: 섬의 개수, M: 다리의 개수
std::vector<std::vector<Edge>> EDGES;   // EDGES[i][j]: i 섬에서 출발할 수 있는 다리 정보
int START, END; // START, END: 공장이 위치해 있는 섬의 번호

int maxCost;    // maxCost: 다리의 최대 중량제한
std::vector<bool> visited;  // visited[i]: i 섬 방문 여부

int answer; // answer: 한 번의 이동에서 옮길 수 있는 물품들의 중량의 최댓값

bool Bfs(int cost){ // cost: 물품들의 중량

    std::queue<int> q;  // q: 갈 수 있는 섬 번호

    q.push(START);
    visited[START] = true;

    while(!q.empty()){
        int curr = q.front();   // curr: 현재 섬 번호
        q.pop();

        if(curr == END) {return true;}  // 도착섬에 도착

        for(const Edge& edge : EDGES[curr]){    // edge: 건널 다리

            if(visited[edge.to] == true) {continue;}    // 이미 방문했다면 conotinue
            if(cost > edge.cost) {continue;}    // 중량을 초과한다면 continue

            q.push(edge.to);
            visited[edge.to] = true;            
        }
    }

    return false;   // 도착섬에 도착하지 못함
}

void Solution(){

    int left = 0, right = maxCost;  // left, right: 물품의 중량 범위

    while(left <= right){
        visited.assign(N+1, false);

        int mid = (left + right) / 2;   // mid: 이번에 시도해볼 중량
        if(Bfs(mid) == true) {left = mid + 1;}  // 도착지점으로 올 수 있다면 -> 더 무겁게 시도
        else {right = mid - 1;} // 도착지점에 오지 못한다면 -> 더 가볍게 시도
    }

    answer = right; // 가능한 가장 무거운 물품들의 중량

    return;
}

void Input(){

    std::cin >> N >> M;

    EDGES.assign(N+1, std::vector<Edge>(0, {0, 0}));

    for(int i=0; i<M; ++i){
        int from, to, cost; // from, to: 다리가 연결되어 있는 섬 번호, cost: 중량제한
        std::cin >> from >> to >> cost;

        EDGES[from].push_back({to, cost});
        EDGES[to].push_back({from, cost});  // 다리는 양방향

        maxCost = std::max(maxCost, cost);  // 이분 탐색을 위해 다리의 최대 중량 구하기 -> 이 중량을 넘어가면 건널 수 있는 다리가 없음
    }

    std::cin >> START >> END;

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