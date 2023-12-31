#include <iostream>
#include <vector>
#include <algorithm>

struct Edge{    // Edge: 행성 연결
    int from, to, cost; // from, to: 연결할 두 행성 번호, cost: 플로우 관리 비용
};

int N;  // N: 행성의 수
std::vector<std::vector<int>> MAP;  // MAP[i][j]: i 행성과 j 행성 간의 플로우 관리 비용

std::vector<int> parent;    // parent[i]: i 행성의 소속
std::vector<Edge> edges;    // edges[i]: 두 행성의 번호와 플로우 관리 비용

long long answer;   // answer: 모든 행성을 연결했을 때 최소 플로우 관리 비용

int Find(int x){    // x: 소속을 찾을 행성 번호
    if(parent[x] == x) {return x;}
    return parent[x] = Find(parent[x]);
}

void Union(int a, int b){   // a, b: 연결할 두 행성 번호
    int pa = Find(a);
    int pb = Find(b);

    if(pa == pb) return;

    if(pa < pb) {parent[pb] = pa;}  // 더 낮은 번호로 소속
    else {parent[pa] = pb;}

    return;
}

bool Cmp(const Edge& left, const Edge& right){  // left, right: 행성 플로우 비용 오름차순 정렬
    if(left.cost != right.cost) {return left.cost < right.cost;}
    return false;
}

void Solution(){

    parent.assign(N+1, 0);

    for(int i=0; i<=N; ++i) {parent[i] = i;}    // 소속정보 초기화

    for(int i=1; i<=N; ++i){
        for(int j=i+1; j<=N; ++j){  // 중복되지 않는 플로우 정보만 입력
            edges.push_back({i, j, MAP[i][j]}); // 플로우 정보 입력
        }
    }

    std::sort(edges.begin(), edges.end(), Cmp); // 플로우 비용을 기준으로 오름차순 정렬

    for(const Edge& edge : edges){  // edge: 연결할 플로우
        if(Find(edge.from) == Find(edge.to)) {continue;}    // 이미 연결되어 있다면 continue

        answer += edge.cost;    // 플로우 비용 추가

        Union(edge.from, edge.to);
    }

    return;
}

void Input(){

    std::cin >> N;

    MAP.assign(N+1, std::vector<int>(N+1, 0));

    for(int i=1; i<=N; ++i){
        for(int j=1; j<=N; ++j){
            std::cin >> MAP[i][j];
        }
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