#include <iostream>
#include <vector>
#include <algorithm>

struct Edge{
	int to;	// to: 연결되어 있는 방
	int cost;	// cost: 연결되어 있는 방까지의 통로의 길이
};

int N;	// N: 동굴의 방의 개수
int robotA, robotB;	// robotA, robotB: 두 로봇이 위치한 방의 번호
std::vector<Edge> v[100'001];	// v[i][j]: i 방과 연결된 j 번째 통로 정보
int path[100'001];	// path[i]: i 번째로 갈 수 있는 통로의 길이
int visited[100'001];	// visited[i]: i 방의 방문 여부
bool flag = true;	// flag: 두 로봇이 위치한 방 까지의 경로를 찾으면 false
int pathDepth;	// pathDepth: 두 로봇이 위치한 방 까지의 경로 길이
int ans;	// ans: 두 로봇이 서로 통신하기 위해 현재 위치에서 이동해야 하는 거리의 합의 최솟값

void DFS(int now, int depth){	// now: 현재 위치한 방의 번호, depth: 현재 까지 지나온 방의 개수

	if(now == robotB){	// robotB가 있는 방에 도착

		pathDepth = depth;
		flag = false;

		return;
	}

	if(flag == false) return;	// 두 로봇을 잇는 경로를 찾앗다면 return

	for(int i=0; i<v[now].size(); i++){
		Edge curEdge = v[now][i];	// curEdge: 탐색을 진행할 통로

		if(visited[curEdge.to] != 0) continue;	// 이미 방문했던 방으로 연결되는 통로면 continue

		visited[curEdge.to] = 1;	// 방문 체크
		path[depth] = curEdge.cost;	// 경로 기록
		DFS(curEdge.to, depth + 1);	// 다음 경로 탐색

		if(flag == false) return;	// 두 로봇을 잇는 경로를 찾았다면 return
	}

	return;
}

void sol(){

	visited[robotA] = 1;
	DFS(robotA, 0);	// robotA가 있는 방부터 탐색을 시작

	int maxCost = 0;	// 경로 사이의 가장 긴 통로 길이
	int sumCost = 0;	// 경로 사이의 모든 통로의 합

	for(int i=0; i<pathDepth; i++){
		sumCost += path[i];
		maxCost = std::max(maxCost, path[i]);
	}

	ans = sumCost - maxCost;	// 모든 통로의 합에서 가장 긴 통로의 길이를 뺌

	return;
}

void input(){

	std::cin >> N >> robotA >> robotB;

	for(int i=0; i<N - 1; i++){
		int from, to, cost;	// from, to: 연결되어 있는 두 방의 번호, cost: 두 방 사이의 통로의 길이
		std::cin >> from >> to >> cost;
		v[from].push_back({to, cost});
		v[to].push_back({from, cost});	// 통로는 양 방향으로 연결
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