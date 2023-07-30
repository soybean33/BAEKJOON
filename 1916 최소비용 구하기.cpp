#include <iostream>
#include <vector>
#include <queue>

constexpr int INF = 10e8;	// INF: 나올 수 없는 값

struct Edge {	// Edge: 버스 정보
	int to;	// to: 갈 수 있는 도시
	int cost;	// cost: 버스 비용

	bool operator < (const Edge& next) const {	// cost를 기준으로 오름차순 정렬
		return cost > next.cost;
	}
};

int N, M;	// N: 도시의 개수, M: 버스의 개수
std::vector<std::vector<Edge>> edge;	// edge[i]: i 도시에서 출발하는 버스 정보
int start, end;	// start: 출발 도시, end: 도착 도시
int ans;	// ans: 출발 도시에서 도착 도시까지 가는데 드는 최소 비용

void solution() {

	std::vector<int> cost;	// cost[i]: 출발 도시에서 i 도시까지 가는데 드는 최소 비용
	cost.assign(N + 1, INF);

	std::priority_queue<Edge> pq;	// pq: cost를 기준으로 오름차순 정렬하는 우선순위 큐

	cost[start] = 0;	// 출발 도시 비용 0
	pq.push({start, 0});

	while(!pq.empty()){
		Edge curr = pq.top();	// curr: 현재 도시
		pq.pop();

		if(cost[curr.to] < curr.cost) continue;	// 이 버스를 탑승하였을 경우 더 많은 비용이 발생하면 continue

		for(const Edge& next : edge[curr.to]) {
			int nextCost = cost[curr.to] + next.cost;	// nextCost: 다음 도시까지 가는데 드는 버스 비용

			if(cost[next.to] <= nextCost) continue;	// 같거나 더 많은 비용이 발생하면 continue

			cost[next.to] = nextCost;
			pq.push({next.to, nextCost});
		}
	}

	ans = cost[end];	// 도착 도시 비용

	return;
}

void input() {

	std::cin >> N;
	std::cin >> M;

	edge.assign(N + 1, std::vector<Edge>(0, {0, 0}));

	for(int i=0; i<M; ++i) {
		int from, to, cost;	// from: 출발 도시, to: 도착 도시, cost: 버스 비용
		std::cin >> from >> to >> cost;
		edge[from].push_back({to, cost});
	}

	std::cin >> start >> end;

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	input();

	solution();

	std::cout << ans;

	return 0;
}