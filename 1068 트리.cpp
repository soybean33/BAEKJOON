#include <iostream>
#include <vector>

int N;	// N: 노드의 개수

std::vector<std::vector<int>> nodes;	// nodes[i][j]: i 노드의 j 번째 부모 노드 번호
int rootNodeNum;	// rootNodeNum: 루트 노드 번호
int removeNode;	// removeNode: 제거된 노드 번호

int answer = 0;	// answer: 리프 노드의 개수

int Dfs(int nodeNum) {	// nodeNum: 현재 노드 번호

	if (nodeNum == removeNode) { return -1; }	// 현재 노드 번호가 제거된 노드 번호인 경우
	if (nodes[nodeNum].size() == 0) {	// 현재 노드가 리프 노드인 경우
		++answer; 
		return 0;
	}

	for (int node : nodes[nodeNum]) {	// node: 다음 노드
		int tmp = Dfs(node);	// tmp: 리프 노드의 결과
		if (tmp == -1 && nodes[nodeNum].size() == 1) { ++answer; }
	}

	return 0;
}

void Solution() {
	
	Dfs(rootNodeNum);

	return;
}

void Input() {

	std::cin >> N;

	nodes.assign(N, std::vector<int>(0, 0));

	for (int i = 0; i < N; ++i) {
		int parent;	// parent: 부모 노드 번호
		std::cin >> parent;
		if (parent == -1) { rootNodeNum = i; }	// 루트 노드의 경우
		else { nodes[parent].push_back(i); }	// 루트 노드가 아닌 경우
	}

	std::cin >> removeNode;

	return;
}

int main() {

	Input();

	Solution();

	std::cout << answer;

	return 0;
}