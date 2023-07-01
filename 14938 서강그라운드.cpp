#include <iostream>
#include <vector>
#include <queue>

const int INF = static_cast<int>(21e8);	// INF: 나올 수 없는 최대 값

struct Edge{	// edge: 길 정보
	int to;	// to: 현재 지역과 연결되어 있는 다음 지역
	int distance;	// distance: 길의 길이

	bool operator < (Edge next) const{	// 길의 길이를 기준으로 오름차순 정렬
		if(distance != next.distance) return distance > next.distance;

		return false;
	}
};

int N, M, R;	// N: 지역의 개수, M: 예은이의 수색 범위, R: 길의 개수
std::vector<int> T;	// T[i]: i 구역에 있는 아이템의 수
std::vector<std::vector<Edge>> edge;	// edge[i][j]: i 지역에 견결되어 있는 j 번째 길 정보
int ans;	// ans: 예은이가 얻을 수 있는 최대 아이템 개수

void dijkstra(int startNode){	// 낙하 지역

	int cnt = 0;	// cnt: 현재 낙하 지역에서 얻을 수 있는 아이템의 개수

	std::vector<int> dist;	// dist[i]: i 지역까지의 거리
	std::priority_queue<Edge> pq;	// pq[i]: i 지역에서의 거리를 기준으로 오름차순 정렬한 길의 정보를 담는 우선 순위 큐

	dist.assign(N, INF);

	dist[startNode] = 0;	// 낙하 지역의 거리는 0
	pq.push({startNode, 0});	// 낙하 지역 넣음

	while(!pq.empty()){
		Edge curr = pq.top();	// curr: 현재 지역
		pq.pop();

		if(dist[curr.to] < curr.distance) continue;	// 연결되어 있는 다음 지역을 이미 더 짧은 거리로 방문 했다면 continue

		for(int i=0; i<edge[curr.to].size(); ++i){
			Edge next = edge[curr.to][i];	// next: 길로 연결되어 있는 길
			int nextDist = dist[curr.to] + next.distance;	// nextDist: next 길로 다음 지역을 방문하였을 때의 거리

			if(dist[next.to] <= nextDist) continue;	// next 길보다 더 짧거나 같은 거리로 갈 수 있었으면 continue

			dist[next.to] = nextDist;	// 지역까지의 거리 갱신

			pq.push({next.to, nextDist});	// 계속 탐색을 위한 우선 순위 큐에 넣음
		}
	}

	for(int i=0; i<N; ++i)
		dist[i] <= M ? cnt += T[i] : 0;	// 예은이의 수색범위에 포함되는 경우 아이템 획득

	ans = std::max(ans, cnt);	// 예은이가 얻을 수 있는 최대 아이템 개수 갱신

	return;
}

void solution(){

	for(int i=0; i<N; ++i) dijkstra(i);	// 모든 지역에서 낙하

	return;
}

void input(){

	std::cin >> N >> M >> R;

	T.assign(N, 0);

	for(int i=0; i<N; ++i) std::cin >> T[i];

	edge.assign(N, std::vector<Edge>(0, {0, 0}));

	for(int i=0; i<R; ++i){
		int A, B, L;	// A, B: 길의 양 끝에 존재하는 지역의 번호, L: 길의 길이
		std::cin >> A >> B >> L;
		edge[A-1].push_back({B-1, L});
		edge[B-1].push_back({A-1, L});	// 양방향
	}

	return;
}

int main(){

	input();

	solution();

	std::cout << ans;

	return 0;
}