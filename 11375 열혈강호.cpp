#include <iostream>
#include <vector>
#include <cstring>

int N, M;	// N: 직원의 수, M: 해야할 일의 수
std::vector<std::vector<int>> work;	// work[i][j]: i 직원이 해야하는 j 번째 일
std::vector<bool> visited;	// visited[i]: 직원이 i 번째 일을 맡음
std::vector<int> parent;	// parent[i]: i 일을 맡은 직원 번호
int ans;	// ans: 할 수 있는 일의 개수

bool Dfs(int curr) {	// curr: 직원 번호
	if(visited[curr]) return false;	// 일을 맡았다면 

	visited[curr] = true;	// 일을 맡음

	for(const int& next : work[curr]) {	// next: 일 번호
		if(!parent[next] || Dfs(parent[next])) {	// 아직 일에 담당자가 없거나 담당자가 있을 경우 새로운 담당자를 배정
			parent[next] = curr;
			return true;
		}
	}

	return false;
}

void Solution() {

	for(int i=1; i<=N; ++i) {	// i 직원에 대하여 일 배정
		visited = std::vector<bool>(N+1, false);	// i 직원이 맡은 일 초기화
		if(Dfs(i)) {++ans;}	// i 직원이 일을 맡았다면 ++
	}

	return;
}

void Input() {

	std::cin >> N >> M;

	// 벡터 생성
	work.assign(N+1, std::vector<int>(0, 0));
	visited.assign(N+1, false);
	parent.assign(M+1, 0);

	for(int i=1; i<=N; ++i) {
		int workCnt;	// workCnt: 할 수 있는 일의 개수
		std::cin >> workCnt;

		for(int j=0; j<workCnt; ++j) {
			int workNum;	// workNum: 일의 번호
			std::cin >> workNum;
			work[i].push_back(workNum);
		}
	}

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();

	std::cout << ans;

	return 0;
}