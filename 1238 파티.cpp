#include <iostream>
#include <vector>
#include <queue>

constexpr int INF = 10e8;	// INF: 나올 수 없는 값

struct Edge {	// Edge: 간선 정보
	int to, time;	// to: 연결되어 있는 마을, time: 소요 시간

	bool operator < (const Edge& next) const {	// time을 기준으로 오름차순 정렬
		return time > next.time;
	}
};

int N, M, X;	// N: 학생의 수, M: 단방향 도로의 개수, X: 파티 마을 번호
std::vector<std::vector<Edge>> edge;	// edge[i]: i 마을에서 시작하는 단방향 도로
std::vector<int> timeToX, timeFromX;	// timeToX[i]: i 마을에서 X 마을까지의 최단 시간, timeFromX[i]: X 마을에서 i 마을까지의 최단 시간
int ans = 0;	// ans: 가장 오래 걸리는 학생의 소요시간

void dijkstra(int start) {	// start: 시작 도시, 0 인경우 X 도시에서 시작

	std::priority_queue<Edge> pq;	// pq: 시간을 기준으로 오름차순 우선순위 큐
	
	if(!start) {	// X 도시에서 시작
		timeFromX.assign(N+1, INF);
		pq.push({X, 0});
		timeFromX[X] = 0;
	}
	else {	// start 도시에서 시작
		timeToX.assign(N+1, INF);
		pq.push({start, 0});
		timeToX[start] = 0;
	}

	while(!pq.empty()) {
		Edge curr = pq.top();	// curr: 현재 간선
		pq.pop();

		// 이미 더 짧은 시간 간선이 있다면 continue
		if(!start) {
			if(timeFromX[curr.to] < curr.time) continue;
		}
		else {
			if(timeToX[curr.to] < curr.time) continue;
		}

		for(const Edge& next : edge[curr.to]) {	// next: 현재 도시에 연결되어 있는 간선
			int nextTime;	// nextTime: 다음 도시까지 가는데 비용
			if(!start) {
				nextTime = timeFromX[curr.to] + next.time;
				if(timeFromX[next.to] <= nextTime) continue;
				timeFromX[next.to] = nextTime;
			}
			else {
				nextTime = timeToX[curr.to] + next.time;
				if(timeToX[next.to] <= nextTime) continue;
				timeToX[next.to] = nextTime;
			}

			pq.push({next.to, nextTime});
		}
	}


	return;
}

void solution() {

	dijkstra(0);	// X에서 시작하여 모든 마을로 탐색

	for(int i=1; i<=N; ++i){

		if(i == X) continue;	// 시작도시와 파티 도시가 같은 경우 할 필요 없음

		dijkstra(i);	// i에서 시작하여 X마을로 탐색

		if(ans < (timeToX[X] + timeFromX[i])) {	// 가장 오래 걸리는 학생의 소요시간
			ans = timeToX[X] + timeFromX[i];
		}		
	}

	return;
}

void input() {

	std::cin >> N >> M >> X;

	edge.assign(N+1, std::vector<Edge>(0, {0, 0}));

	for(int i=0; i<M; ++i){
		int from, to, time;	// from: 시작 도시, to: 끝 도시, time: 도로를 지나는데 필요한 소요시간

		std::cin >> from >> to >> time;

		edge[from].push_back({to, time});	// 단방향 도로
	}

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