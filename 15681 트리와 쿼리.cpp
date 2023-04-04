#include <iostream>
#include <vector>

std::vector<int> v[100001];	// v[i]: i 정점과 연결된 정점
int DAT[100001];	// DAT[i]: i 정점의 자신을 포함한 자식 정점의 수
int visited[100001];	// visited[i]: 방문 검사

void DFS(int node) {	// node: 현재 정점

	int size = v[node].size();	// size: node 정점과 연결된 정점의 수 -> 부모 정점과 자식 정점을 모두 포함

	int cnt = 0;	// cnt: 자식 정점의 수
	visited[node] = 1;	// node 방문 체크
	for (int s = 0; s < size; s++) {
		int nextNode = v[node][s];	// nextNode: 다음에 방문할 정점
		if (visited[nextNode] != 0) continue;	// 이미 방문한 정점이면 (=부모 정점이면) continue
		
		cnt++;	// 자식 정점 수 증가
	}

	if (cnt == 0) {	// 더 이상 자식 정점이 없다면
		DAT[node] = 1;	// 가장 말단 정점이므로 값은 1

		return;
	}

	for(int s=0; s<size; s++){
		int nextNode = v[node][s];	// nextNode: 다음에 방문할 정점
		if (visited[nextNode] != 0) continue;	// 이미 방문한 정점이면 (=부모 정점이면) continue
		
		DFS(v[node][s]);	// 자식 정점으로 이동

		if (DAT[nextNode] != 0) {	// 자식 정점의 값이 0이 아니면 -> 이미 nextNode 아래는 확인할 필요 없음
			if (DAT[node] == 0)	// 정점이 자기 자신을 포함하고 있지 않으면
				DAT[node] = 1;	// 자기 자신을 포함
			DAT[node] += DAT[nextNode];	// 자식 노드의 자식 노드의 수를 더함
		}
	}

	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int N, R, Q;	// N: 트리의 정점의 수, R: 루트이 번호, Q: 쿼리의 수
	std::cin >> N >> R >> Q;

	for (int i = 0; i < N -1; i++) {	// 주어지는 간선은 N-1개
		int a, b;	// a: 정점1, b: 정점2 -> 정점1과 정점2가 간선으로 연결
		std::cin >> a >> b;
		v[a].push_back(b);
		v[b].push_back(a);	// 양방향 연결
	}

	DFS(R);

	for (int i = 0; i < Q; i++) {
		int a;	// a: 정점
		std::cin >> a;
		std::cout << DAT[a] << '\n';	// a 정점의 자신을 포함한 자식 노드의 수
	}	

	return 0;
}