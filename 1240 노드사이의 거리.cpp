#include <iostream>
#include <vector>
#include <queue>

struct Edge{	// Edge: 간선 구조체
	int to;	// to: 다음 노드 번호
	int dist;	// dist: 다음 노드 까지의 거리
};

int N, M;	// N: 노드의 개수, M: 거리를 구할 노드 쌍의 개수
std::vector<std::vector<Edge>> edges;	// edges[i][j]: i 노드에 연결되어 있는 j 번째 간선

void Solution(){

	while(M--){	// M개의 노드 쌍에 대하여

		int nodeA, nodeB;	// nodeA, nodeB: 거리를 알고 싶은 두 노드의 번호
		std::vector<bool> visited;	// visited[i]: i 노드 방문 여부

		std::cin >> nodeA >> nodeB;
		visited.assign(N + 1, false);

		std::queue<Edge> q;	// q: 탐색할 간선 정보를 저장할 큐
		q.push({nodeA, 0});
		visited[nodeA] = true;	// 시작 노드 방문 체크

		while(!q.empty()){
			Edge curr = q.front();	// curr: 이번에 탐색할 간선
			q.pop();

			if(curr.to == nodeB) {	// 찾는 노드와 일치한 경우
				std::cout << curr.dist << '\n';
				break;
			}

			for(const Edge& edge : edges[curr.to]) {	// edge: 현재 노드에 연결되어 있는 간선
				if(visited[edge.to] == true) {continue;}	// 이미 방문 했다면 continue

				Edge next = {edge.to, curr.dist + edge.dist};	// next: 탐색에 사용할 다음 간선 정보 갱신 -> 현재 까지의 거리에 갈 거리를 더함

				visited[next.to] = true;	// 방문 체크
				q.push(next);	// 탐색에 사용할 수 있도록 큐에 넣음
			}
		}
	}
	
	return;
}

void Input(){

	std::cin >> N >> M;

	edges.assign(N + 1, std::vector<Edge>(0, {0, 0}));

	for(int i=0; i<N-1; ++i){
		int nodeA, nodeB, dist;	// nodeA, nodeB: 연결되어 있는 간선, dist: 연결되어 있는 두 간선 사이의 거리
		
		std::cin >> nodeA >> nodeB >> dist;

		edges[nodeA].push_back({nodeB, dist});
		edges[nodeB].push_back({nodeA, dist});
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();

	return 0;
}