#include <iostream>
#include <vector>
#include <queue>

int V, E;	// V: 정점의 개수, E: 간선의 개수
std::vector<std::vector<int>> edges;	// edges[i][j]: i 정점과 연결되어 있는 j 번째 노드 번호
std::vector<int> visited;	// visited[i]: i 노드의 타입
bool flag;	// flag: 이분 그래프라면 true, 이분 그래프가 아니면 false

void Bfs(int start){	// start: 탐색 시작 노드
	std::queue<int> q;
	
	q.push(start);
	visited[start] = 1;	// 타입이 없는 노드는 1번 타입을 갖음

	while(!q.empty()){
		int curr = q.front();	// curr: 현재 노드 번호
		q.pop();

		int nextType = (visited[curr]) % 2 + 1;	// nextType: 다음 노드 타입

		for(const int& next : edges[curr]) {	// next: 연결되어 있는 노드 번호
			if(visited[next] != 0) {continue;}	// 이미 타입이 정해져있다면 continue

			q.push(next);
			visited[next] = nextType;
		}
	}
}

void Solution(){

	visited.assign(V, 0);

	for(int i=0; i<V; ++i){
		if(visited[i] != 0) {continue;}	// 타입이 정해졌다면 continue
		Bfs(i);
	}

	flag = true;

	for(int i=0; i<V; ++i){
		for(const int& node : edges[i]) {	// node: 노드 번호
			if(visited[i] == visited[node]) {	// 인접한 두 노드가 같은 타입을 갖는다면 이분 그래프가 아님
				flag = false;
				break;
			}
		}
		if(flag == false) {break;}
	}


	return;
}

void Input(){

	std::cin >> V >> E;

	edges.assign(V, std::vector<int>(0, 0));

	for(int i=0; i<E; ++i){
		int to, from;	// to, from: 연결되어 있는 두 노드 번호
		std::cin >> to >> from;
		--to;
		--from;
		edges[to].push_back(from);
		edges[from].push_back(to);	// 양방향 연결
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int K;	// K: 테스트 케이스의 개수

	std::cin >> K;

	while(K--){
		Input();
		Solution();

		if(flag) {std::cout << "YES\n";}
		else {std::cout << "NO\n";}
	}

	return 0;
}