#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

// 방향 벡터
constexpr int dirY[4] = {0, 1, 0, -1};
constexpr int dirX[4] = {1, 0, -1, 0};

struct Coordinate{	// 좌표
	int y, x;
};

int N, M;	// N, M: 보물섬 지도의 세로, 가로 길이
std::vector<std::vector<int>> MAP;	// MAP[i][j]: i 행 j 열의 육지(0), 바다(-1)

int answer;	// answer: 보물이 뭍혀 있는 두 곳 간의 최단 거리로 이동하는 시간

void Solution(){

	for(int y=0; y<N; ++y){
		for(int x=0; x<M; ++x){
			if(MAP[y][x] == - 1) {continue;}	// 바다에서는 시작할 필요 없으므로 continue

			std::vector<std::vector<int>> visited;	// visited[i][j]: i 행 j 열까지 가는데 걸리는 거리
			visited.assign(N, std::vector<int>(M, 0));

			std::queue<Coordinate> q;	// q: 다음 탐색 좌표를 저장하는 큐

			visited[y][x] = 1;
			q.push({y, x});

			while(!q.empty()){
				Coordinate curr = q.front();	// curr: 현재 좌표
				q.pop();

				for(int dir=0; dir<4; ++dir){
					Coordinate next = {curr.y + dirY[dir], curr.x + dirX[dir]};	// next: 다음 좌표

					if(next.y < 0 || next.x < 0 || next.y >= N || next.x >= M) {continue;}	// 좌표 벗어나면 continue

					if(MAP[next.y][next.x] == -1) {continue;}	// 다음 좌표가 바다인 경우 continue
					if(visited[next.y][next.x] != 0) {continue;}	// 다음 좌표에 이미 방문한 경우 continue

					visited[next.y][next.x] = visited[curr.y][curr.x] + 1;	// 거리 값 저장
					q.push(next);

					answer = std::max(answer, visited[next.y][next.x] - 1);	// answer: 보물이 뭍혀 있는 두 곳 같의 최단 거리
				}
			}
		}
	}

	return;
}

void Input(){

	std::cin >> N >> M;
	MAP.assign(N, std::vector<int>(M, 0));

	for(int y=0; y<N; ++y){
		for(int x=0; x<M; ++x){
			char c;	// c: L: 육지, W: 바다
			std::cin >> c;
			MAP[y][x] = c == 'W' ? -1 : 0;	// 바다는 -1, 육지는 0
		}
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();
	
	std::cout << answer;

	return 0;
}