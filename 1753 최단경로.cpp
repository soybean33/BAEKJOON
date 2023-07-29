#include <iostream>
#include <vector>
#include <queue>

constexpr int INF = 10e8;	// INF: 나올 수 없는 값

struct Edge{	// Edge: 간선의 정보
	int to, weight;	// to: 연결되어 있는 정점, weight: 간선의 가중치

	bool operator < (const Edge& next) const {
		return weight > next.weight;	// 가중치를 기준으로 오름차순 정렬하는 우선순위 큐
	}
};


int V, E;	// V: 정점의 개수, E: 간선의 개수
int start;	// start: 시작 정점의 번호
std::vector<std::vector<Edge>> edge;	// edge[i][j]: i 정점에서 시작하는 j 번째 간선 정보
std::vector<int> weight;	// weight[i]: i 정점까지의 최단 가중치

void solution(){

	std::priority_queue<Edge> pq;	// pq: 가중치를 기준으로 오름차순 정렬한 우선 순위 큐
	weight.assign(V, INF);	// 최단 가중치 초기화

	// 시작 정점부터 탐색
	pq.push({start, 0});
	weight[start] = 0;

	while(!pq.empty()){
		Edge curr = pq.top();	// curr: 현재 정점
		pq.pop();

		if(weight[curr.to] < curr.weight) continue;	// 이미 더 짧은 가중치로 다음 정점에 방문할 수 있다면 continue

		for(const Edge& next : edge[curr.to]){	// next: 이번 정점에 연결되어 있는 간선
			int nextWeight = weight[curr.to] + next.weight;	// nextWeight: 선택된 간선을 사용하였을 경우 다음 정점에 도착하였을 경우의 가중치

			if(weight[next.to] <= nextWeight) continue;	// 이미 더 짧거나 같은 가중치로 다음 정점에 방문할 수 있다면 continue

			weight[next.to] = nextWeight;	// 가중치 갱신

			pq.push({next.to, nextWeight});	// 다음 탐색 할 간선 정보 입력
		}
	}

	return;
}

void input(){

	std::cin >> V >> E;

	std::cin >> start;
	start--;

	edge.assign(V, std::vector<Edge>(0, {0, 0}));

	for(int i=0; i<E; ++i){
		int u, v, w;	// u: 출발 정점, v: 도착 정점, w: 간선의 가중치
		std::cin >> u >> v >> w;

		edge[u-1].push_back({v-1, w});
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	input();

	solution();

	for(int i=0; i<V; ++i){
		if(weight[i] == INF) std::cout << "INF\n";
		else std::cout << weight[i] << '\n';
	}

	return 0;
}