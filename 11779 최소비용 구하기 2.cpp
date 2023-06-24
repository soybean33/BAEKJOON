#include <iostream>
#include <vector>
#include <queue>

struct Edge{	// 간선 정보
	int to;	// to: 연결되어 있는 도시 번호
	int cost;	// cost: 도시 까지 가는데 드는 비용

	bool operator < (Edge next) const {	// 비용을 기준으로 오름차순 정렬한 우선 순위 큐
		if(cost != next.cost) return cost > next.cost;

		return false;
	}
};

int n, m;	// n: 도시의 개수, m: 버스의 개수
std::vector<Edge> v[1'001];	// v[i]: i 번 도시에서 출발하는 버스의 정보
int start, end;	// start: 출발 도시, end: 도착 도시
std::vector<int> dist;	// dist[i]: 출발 도시에서 i 도시 까지의 최소 비용
std::vector<int> path;	// path[i]: 출발 도시에서 i 도시 까지 최소 비용이 되기 위한 i 의 전 도시
std::vector<int> ans;	// ans[i]: 최소 비용을 갖는 경로를 방문하는 도시의 역순

void sol(){

	// 도시의 갯수 만큼 할당
	dist.resize(n + 1);
	path.resize(n + 1);

	std::priority_queue<Edge> pq;	// pq: 비용을 기준으로 오름차순 정렬한 우선 순위 큐
	pq.push({start, 0});	// 출발 도시

	for(int i = 0; i < n + 1; i++) dist[i] = 21e8;	// 초기 거리 정보 큰 값 넣음
	dist[start] = 0;	// 시작 도시는 0의 값

	while(!pq.empty()){
		Edge cur = pq.top();	// cur: 현재 위치한 도시
		pq.pop();

		if(dist[cur.to] < cur.cost) continue;	// 현재 도시에서 가고자 하는 도시의 비용이 현재 비용보다 작다면 continue

		for(int i = 0; i < v[cur.to].size(); i++){
			Edge next = v[cur.to][i];	// next: 현재 도시에서 갈 수 있는 간선 정보
			int nextCost = dist[cur.to] + next.cost;	// nextCost: next 간선을 사용하여 다음 도시에 도착하였을 때의 비용

			if(dist[next.to] <= nextCost) continue;	// 더 큰 비용이 발생한다면 continue

			dist[next.to] = nextCost;	// 거리 정보 갱신
			path[next.to] = cur.to;	// 경로 정보 갱신

			pq.push({next.to, nextCost});	// 간선 추가
		}
	}

	int curCity = end;	// curCity: 경로를 알기 위한 현재 도시
	while(true){
		if(curCity == start) {	// 출발 도시 까지 탐색 완료
			ans.push_back(curCity);
			break;
		}
		ans.push_back(curCity);
		curCity = path[curCity];
	}

	return;
}

void input(){

	std::cin >> n >> m;

	for(int i = 0; i < m; i++){
		int from, to, cost;	// from: 출발 도시, to: 도착 도시, cost: 비용
		std::cin >> from >> to >> cost;
		v[from].push_back({to, cost});
	}

	std::cin >> start >> end;

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	sol();

	std::cout << dist[end] << '\n';
	std::cout << ans.size() << '\n';

	while(!ans.empty()){
		std::cout << ans.back() << ' ';
		ans.pop_back();
	}

	return 0;
}