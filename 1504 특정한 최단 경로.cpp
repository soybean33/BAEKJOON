#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct Edge{	// Edge: 간선
	int to;	// to: 이어져 있는 정점
	int cost;	// cost: 거리

	bool operator < (Edge next) const {	// 거리를 기준으로 오름차순 정렬한 우선 순위 큐
		if(cost != next.cost) return cost > next.cost;

		return false;
	}
};

int N, E;	// N: 정점의 개수, E: 간선의 개수
std::vector<Edge> v[200'001];	// v[i]: i 정점과 연결되어 있는 간선 정보 -> {정점, 거리}
int v1, v2;	// v1, v2: 반드시 거쳐야 하는 두 개의 서로 다른 정점 번호
std::vector<int> cost;	// cost[i]: i 정점까지의 최단 거리
int ans = 21e8;	// ans: 두 개의 정점을 지나는 최단 경로의 길이

void dijkstra(int start){

	std::priority_queue<Edge> pq;	// pq: 거리를 기준으로 오름차순 정렬한 우선 순위 큐

	for(int i=0; i<N+1; i++) cost[i] = 21e8;	// 최단 거리 최기화

	// start 부터 출발, 거리는 0
	pq.push({start, 0});
	cost[start] = 0;

	while(!pq.empty()){
		Edge cur = pq.top();	// cur: 현재 정점
		pq.pop();

		if(cost[cur.to] < cur.cost) continue;	// 현재 정점에서 다음 정점까지의 거리가 지금의 간선을 사용해서 가는 것 보다 가까우면 continue

		for(int i=0; i<v[cur.to].size(); i++){	// 현재 정점과 연결되어 있는 모든 간선에 대하여 반복
			Edge next = v[cur.to][i];	// next: 핸재 정점과 연결되어 있는 간선
			int nextCost = cost[cur.to] + next.cost;	// nextCost: next 간선을 사용하여 이동하였을 때의 거리

			if(cost[next.to] <= nextCost) continue;	// next 간선을 사용하였을 때, 이전의 다른 간선을 사용한 거리보다 멀면 continue

			cost[next.to] = nextCost;	// 최단 거리 갱신
			pq.push({next.to, next.cost});	// 해당 간선을 타고 다음 간선으로 이동
		}
	}

	return;;
}

void solution(){

	cost.resize(N + 1);	// 정점의 번호를 갖도록 공간 할당

	dijkstra(1);	// 1번 정점에서 출발 -> v1 까지와 v2 까지의 최단 거리 계산
	int startToV1 = cost[v1];	// startToV1: 출발 정점에서 v1 정점 까지의 최단 거리
	int startToV2 = cost[v2];	// startToV2: 출발 정점에서 v2 정점 까지의 최단 거리
	if(startToV1 == 21e8 && startToV2 == 21e8){	// 출발 정점에서 v1, v2 까지의 경로가 모두 존재 하지 않으면 -1 return
		ans = -1;
		return;
	}

	dijkstra(v1);	// v1 정점에서 출발 -> v2 까지와 도착 정점 까지의 최단 거리 계산
	int v1ToV2 = cost[v2];	// v1ToV2: v1 과 v2 사이의 최단 거리 계산 -> 이 경로는 필수 적으로 필요
	int v1ToEnd = cost[N];	// v1ToEnd: v1 정점에서 도착 정점 까지의 최단 거리 
	if(v1ToV2 == 21e8){	// v1 정점과 v2 정점 경로가 존재 하지 않으면 -1 return
		ans = -1;
		return;
	}

	dijkstra(v2);	// v2 정점에서 출발 -> 도착 정점 까지의 최단 거리 계산
	int v2ToEnd = cost[N];	// v2ToEnd: v2 정점에서 도착 정점 까지의 최단 거리
	if(v1ToEnd == 21e8 && v2ToEnd == 21e8){	// v1 정점과 v2 정점에서 도착 정점 까지의 경로가 모두 존재하지 않으면 -1 return
		ans = -1;
		return;
	}

	ans = std::min(ans, startToV1 + v1ToV2 + v2ToEnd);	// 출발 -> v1 -> v2 -> 도착
	ans = std::min(ans, startToV2 + v1ToV2 + v1ToEnd);	// 출발 -> v2 -> v1 -> 도착

	return;
}

void input(){

	std::cin >> N >> E;

	for(int i=0; i<E; i++){
		int from, to, cost;	// from, to: 연결되어 있는 두 정점 -> 양방향, cost: 두 정점의 거리
		
		std::cin >> from >> to >> cost;
		v[from].push_back({to, cost});
		v[to].push_back({from, cost});
	}

	std::cin >> v1 >> v2;

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	solution();

	std::cout << ans;

	return 0;
}