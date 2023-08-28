#include <iostream>
#include <vector>

int Solution(const int& n, const std::vector<int>& parent, int& a, int& b) {

	std::vector<bool> visited;	// visited[i]: i 노드 방문 여부

	visited.assign(n+1, false);
	visited[a] = true;	// a 노드 부터 시작

	while(a != parent[a]) {	// a 노드 부터 시작하여 루트 노드를 찾을 때 까지 반복
		a = parent[a];
		visited[a] = true;
	}
	while(true) {
		if(visited[b]) {return b;}	// b 노드 부터 시작하여 루트 노드까지 탐색하면서 방문했던 노드를 찾는다면 가장 가까운 공통 조상
		b = parent[b];
	}


	return 0;
}

void Input(int& n, std::vector<int>& parent, int& a, int& b) {

	std::cin >> n;

	parent.assign(n+1, 0);

	for(int i=1; i<=n; ++i) {parent[i] = i;}

	for(int i=0; i<n-1; ++i) {
		int u, v;
		std::cin >> u >> v;
		parent[v] = u;	// 부모 정보 입력
	}

	std::cin >> a >> b;

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int t;	// t: 테스트 케이스의 개수
	std::cin >> t;

	while(t--) {

		int n;	// n: 트리를 구성하는 노드의 수 2 <= n <= 10,000
		std::vector<int> parent;	// parent[i]: i 노드의 부모 노드 번호
		int a, b;	// a, b: 가장 가까운 공통 조상을 구할 두 노드

		Input(n, parent, a, b);

		std::cout << Solution(n, parent, a, b) << '\n';
	}

	return 0;
}