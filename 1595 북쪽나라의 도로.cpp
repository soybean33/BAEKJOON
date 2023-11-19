#include <iostream>
#include <vector>
#include <algorithm>

struct Edge{    // Edge: 도로 정보
    int to, distance;   // to: 도착 도시, distance: 거리
};

std::vector<std::vector<Edge>> edges;   // edges[i]: i 도시에 연결되어 있는 도로 정보
std::vector<bool> visited;  // visited[i]: i 도시 방문 여부

int answer; // answer: 가장 거리가 먼 두 도시간의 거리

void Dfs(int node, int dist){   // node: 현재 도시 번호, dist: 현재 도시 까지 오는데 거리

    answer = std::max(answer, dist);

    for(const Edge& edge : edges[node]){    // edge: 연결되어 있는 도로 정보
        if(visited[edge.to] == true) {continue;}    // 이미 방문 했다면 continue

        visited[edge.to] = true;
        Dfs(edge.to, dist + edge.distance);
    }

    return;
}

void Solution(){

    for(int i=1; i<=10'000; ++i){
        if(edges[i].size() == 0) {continue;}    // 도시에 연결된 도로가 없다면 continue

        visited.assign(10'001, false);
        visited[i] = true;  // 방문 체크

        Dfs(i, 0);
    }

    return;
}

void Input(){

    int A, B, D;    // A, B: 도로로 연결되어 있는 두 도시, D: 두 도시를 연결하는 도로의 길이
    edges.assign(10'001, std::vector<Edge>(0, {0, 0}));

    while(std::cin >> A >> B >> D){
        edges[A].push_back({B, D});
        edges[B].push_back({A, D}); // 양방향 연결
    }

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