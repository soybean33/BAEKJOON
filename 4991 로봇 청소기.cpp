#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

struct Coordinate {
	int y, x;	// y, x: 좌표
};

struct Cleaner {
	int num;	// num: 로봇 청소기 번호
	Coordinate loc;	// loc: 로봇 청소기 위치
};

struct Edge {
	int to;	// 연결되어 있는 정점
	int distance;	// distance: 거리
	
};

// 방향 벡터: 우 상 좌 하
int dirY[] = { 0, -1, 0, 1 };
int dirX[] = { 1, 0, -1, 0 };

std::vector<Edge> v[11];	// v[i]: 정점 i와 연결되어 있는 정점의 번호와 거리
int visited[11];	// visited[i]: 방문한 정점
int minDistance;	// minDistance: 더러운 칸을 모두 깨끗한 칸으로 만드는데 필요한 이동 횟수의 최솟값

void DFS(int node, int distance, int depth) {	// node: 현재 정점, distance: 현재까지 이동한 거리, depth: 제거한 먼지의 수

	if (depth == 0) {	// 모든 먼지 제거
		minDistance = std::min(minDistance, distance);	// 최소 이동 거리 갱신
		return;
	}

	int size = v[node].size();	// size: node 정점과 연결되어 있는 정점의 수

	for (int i = 0; i < size; i++) {
		int nextNode = v[node][i].to;	// nextNode: 다음 정점

		if (visited[nextNode] != 0) continue;	// 이미 연결되어 있는 정점 continue

		visited[nextNode] = 1;	// 연결
		DFS(nextNode, distance + v[node][i].distance, depth - 1);
		visited[nextNode] = 0;	// 연결 해재
	}

	return;
}

int sol() {

	Cleaner cleaner;	// cleaner: 로봇 청소기
	int MAP[21][21] = { 0, };	// MAP[i][j]: 방의 i행 j열의 정보 -> 0 빈 공간, -1 가구, 1 ~ 먼지 혹은 로봇 청소기
	int w, h, dirtyNum = 0;	// w: 방의 가로 길이, h: 방의 세로 길이, dirtyNum: 먼지와 로봇 청소기의 수

	for (int i = 0; i < 11; i++) {
		while (!v[i].empty()) v[i].pop_back();	// 연결 정보 초기화
		visited[i] = 0;	// 연결 정보 초기화
	}

	std::cin >> w >> h;

	if (w == 0 && h == 0) return -2;	// (0, 0)이 입력되면 종료

	for (int j = 0; j < h; j++) {
		std::string s;	// s: 방의 한 행 정보
		std::cin >> s;
		for (int i = 0; i < w; i++) {
			char c = s[i];	// c: 방의 정보
			if (c == '.') MAP[j][i] = 0;	// 빈 공간
			if (c == '*' || c == 'o') {	// 먼지나 로봇 청소기
				dirtyNum++;
				MAP[j][i] = dirtyNum;
				if (c == 'o')	// 로봇 청소기 정보 저장
					cleaner = { dirtyNum, {j, i} };
			}
			if (c == 'x') MAP[j][i] = -1;	// 가구
		}
	}

	for (int j = 0; j < h; j++) {
		for (int i = 0; i < w; i++) {
			if (MAP[j][i] <= 0) continue;	// 빈 공간이거나 벽인 경우 continue

			std::queue<Coordinate> q;	// q: 이동할 곳
			int visited[21][21] = { 0, };	// visited[i][j]: 방문할 곳
			int cnt = 0;	// cnt: 각 정점에서 갈 수 있는 정점의 수 -> dirtyNum과 다르면 갈 수 없는 곳이 있음
			int cur_Node = MAP[j][i];	// cur_node: 현재 정점

			q.push({ j, i });
			visited[j][i] = 1;
			cnt++;

			while (!q.empty()) {
				Coordinate cur = q.front();	// cur: 현재 정점 정보
				q.pop();

				for (int dir = 0; dir < 4; dir++) {
					Coordinate next = { cur.y + dirY[dir], cur.x + dirX[dir] };	// next: 다음으로 갈 정점

					if (next.y < 0 || next.x < 0 || next.y >= h || next.x >= w) continue;	// 방의 범위를 벗어나면 continue
					if (MAP[next.y][next.x] == -1) continue;	// 가구 continue
					if (visited[next.y][next.x] != 0) continue;	// 이미 방문한 칸 continue

					visited[next.y][next.x] = visited[cur.y][cur.x] + 1;	// 거리 증가

					if (MAP[next.y][next.x] > 0) {	// 먼지나 로봇 청소기가 있다면
						int next_Node = MAP[next.y][next.x];	// next_Node: 먼지나 로봇 청소기의 정점 번호
						cnt++;
						v[cur_Node].push_back({next_Node, visited[next.y][next.x] - 1});	// 연결 정보 추가
					}

					q.push(next);
				}
			}
			if (cnt != dirtyNum)	// 각 정점에서 모든 정점에 도달할 수 없다면 return -1
				return -1;
		}
	}	

	minDistance = 21e8;	// 최소거리 최대값으로 초기화
	visited[cleaner.num] = 1;	// 로봇 청소기 위치부터 시작하므로 방문 체크
	DFS(cleaner.num, 0, dirtyNum - 1);	// 로봇 청소기 부터 DFS

	return minDistance;
}

int main() {

	while (true) {
		int ans = sol();

		if (ans == -2)	// (0, 0)이 입력됨
			break;

		std::cout << ans << '\n';
	}		

	return 0;
}