#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int T;  // T: 테스트케이스의 개수
int N, K;   // N: 건물의 개수, K: 건물간의 건설 순서 규칙의 개수

std::vector<int> COST;  // COST[i]: i 건물을 짓는데 걸리는 시간
std::vector<std::vector<int>> EDGE; // EDGE[i]: i 번째 건물 다음에 짓는 건물의 번호

int W;  // W: 건물의 번호

std::vector<int> resultCost;    // resultCost[i]: 순서대로 건물을 지었을 때 건물을 짓는데 걸리는 시간
std::vector<int> indegree;  // indegree[i]: i 건물을 짓기 위해 지어야하는 건물의 수

int answer; // answer: 건물 W를 건설완료 하는데 드는 최소 시간

void Solution(){

    std::queue<int> q;  // q: 지금 당장 지을 수 있는 건물 번호

    for(int i=1; i<=N; ++i){
        if(i == W) {continue;}
        else if(indegree[i] == 0) {q.push(i);}  // 먼저 지어야할 건물이 없다면 후보에 올림
    }

    while(!q.empty()){
        int curr = q.front();   // curr: 지을 수 있는 건물 번호
        q.pop();

        for(const int& next : EDGE[curr]) { // next: 현재 건물 다음에 지을 수 있는 건물 번호
            resultCost[next] = std::max(resultCost[next], resultCost[curr] + COST[next]);   // 건물을 짓는데 더 큰 시간이 걸리는 것으로 갱신
            if(--indegree[next] == 0) {q.push(next);}   // 앞써 지어야하는 건물이 없다면 지을 수 있는 건물 후보에 올림
        }
    }

    answer = resultCost[W]; // W 건물을 지을 때 걸리는 시간

    return;
}

void Input(){

    std::cin >> N >> K;

    COST.assign(N+1, 0);
    resultCost.assign(N+1, 0);

    for(int i=1; i<=N; ++i) {
        int cost;   // cost: 건물을 짓는데 걸리는 시간
        std::cin >> cost;
        COST[i] = cost;
        resultCost[i] = cost;
    }

    EDGE.assign(N+1, std::vector<int>(0, 0));
    indegree.assign(N+1, 0);

    for(int i=0; i<K; ++i){
        int to, from;   // to, from: to 건물 다음에 from 건물을 지을 수 있음
        std::cin >> to >> from;

        EDGE[to].push_back(from);
        ++indegree[from];   // from 건물 앞에 지어야하는 건물의 수 증가
    }

    std::cin >> W;

    return;
}

int main(){

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> T;

    for(int tc=0; tc<T; ++tc){
        Input();
        Solution();
        std::cout << answer << '\n';
    }

    return 0;
}