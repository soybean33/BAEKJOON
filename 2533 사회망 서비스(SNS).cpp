#include <iostream>
#include <vector>
#include <algorithm>

int N;	// N: 친구 관계 트리의 정점 개수
std::vector<int> v[1'000'001];	// v[i][j]: i 노드와 연결되어 있는 j 번째 노드 번호
int dp[1'000'001][2];	// dp[i][j]: i 노드의 j 상태에서의 최소 값 -> 0: 해당 노드가 얼리 어답터일 경우, 1: 해당 노드가 일반인일 경우
int visited[1'000'001];	// visited[i]: i 노드의 방문 여부
int ans;	// ans: 주어진 친구 관계 그래프에서 아이디어를 전파하는데 필요한 얼리 어답터의 최소 수

void DFS(int now){	// now: 현재 노드 번호

	dp[now][0] = 1;	// 현재 노드가 일반인일 경우, 현재 노드 + 현재 노드의 모든 자식 노드 중 조건을 만족하는 최소 얼리어답터의 수

	for(int i=0; i<v[now].size(); i++){
		int child = v[now][i];	// child: 현재 노드의 자식 노드 번호

		if(visited[child] != 0) continue;	// 이미 방문한 노드 continue

		visited[child] = 1;	// 방문 체크

		DFS(child);

		dp[now][1] += dp[child][0];	// 현재 노드가 일반인일 경우, 해당 노드의 모든 자식노드 중 문제의 조건을 만족하는 최소 얼리어답터의 수
		dp[now][0] += std::min(dp[child][0], dp[child][1]);	// 현재 노드가 얼리어답터일 경우, 해당 노드의 모든 자식노드 중 문제의 조건을 만족하는 최소 얼리어답터의 수
	}

	return;
}

void sol(){

	visited[1] = 1;
	DFS(1);	// 1번 노드부터 탐색

	ans = std::min(dp[1][0], dp[1][1]);	// 주어진 친구 관계 그래프에서 아이디어를 전파하는데 필요한 얼리 어답터의 최소 수

	return;
}

void input(){

	std::cin >> N;

	for(int i=0; i<N-1; i++){
		int nodeA, nodeB;	// nodeA, nodeB: 친구 관계
		std::cin >> nodeA >> nodeB;
		v[nodeA].push_back(nodeB);
		v[nodeB].push_back(nodeA);	// 양방향
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	sol();

	std::cout << ans;

	return 0;
}