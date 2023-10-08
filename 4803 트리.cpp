#include <iostream>
#include <vector>

int N, M;	// N: 정점의 개수, M: 간선의 개수
std::vector<std::vector<int>> nodes;	// edges[i][j]: i 정점과 연결되어 있는 j 번째 정점 번호
std::vector<bool> visited;	// visited[i]: i 정점 방문 여부

int answer;	// answer: 트리의 개수

bool Dfs(int curr, int prev) {	// curr: 현재 정점, prev: 이전 정점

	visited[curr] = true;	// 현재 정점 방문 체크

	for(const int& next : nodes[curr]) {	// next: 현재 정점과 연결되어 있는 정점 번호
		if(next == prev) {continue;}	// 양 방향으로 연결되어 있으므로 왔던 정점으로 돌아가지 않도록 주의

		if(visited[next]) {return false;}	// 이미 방문한 정점을 방문하는 경우에는 사이클이 발생하므로 return false
		if(Dfs(next, curr) == false) {return false;}	// 이미 트리가 구성되지 않는 경우 return fasle
	}

	return true;
}

void Solution(){

	answer = 0;

	visited.assign(N+1, false);	// 방문 초기화

	for(int i=1; i<=N; ++i){	// 모든 정점에 대하여 검사
		if(visited[i] == true) {continue;}	// 이미 방문한 정점은 continue
		if(Dfs(i, 0)) {++answer;}	// 트리가 만들어 짐
	}

	return;
}

void Input(){

	nodes.assign(N + 1, std::vector<int>(0, 0));

	for(int i=0; i<M; ++i){
		int nodeA, nodeB;	// nodeA, nodeB: 연결되어 있는 두 정점
		std::cin >> nodeA >> nodeB;

		nodes[nodeA].push_back(nodeB);
		nodes[nodeB].push_back(nodeA);	// 양방향 연결
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int tc = 1;	// tc: 테스트 케이스 번호

	while(true) {
		std::cin >> N >> M;
		if(N == 0 && M == 0) {break;}	// 0 0 이 입력되면 반복 종료

		Input();
		Solution();
		
		std::cout << "Case " << tc << ": ";
		if(answer == 0) {	// 그래프에 트리가 없다면
			std::cout << "No trees.\n";
		}
		else if(answer == 1) {	// 그래프에 트리가 한 개 라면
			std::cout << "There is one tree.\n";
		}
		else{	// 그래프에 트리가 한 개 이상 이라면
			std::cout << "A forest of " << answer << " trees.\n";
		}
		++tc;
	}

	return 0;
}