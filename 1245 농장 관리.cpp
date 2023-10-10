#include <iostream>
#include <vector>
#include <queue>

// X좌표 차이와 Y좌표 차이 모두 1 이하일 경우를 나타내는 방향 벡터
constexpr int dirY[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
constexpr int dirX[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

// Coordinate: 좌표
struct Coordinate{
	int y, x;
};

int N, M;	// N: 농장의 세로, M: 농장의 가로
std::vector<std::vector<int>> MAP;	// MAP[i][j]: i 행 j 열의 높이

int answer;	// answer: 산봉우리의 개수

void Solution(){

	std::vector<std::vector<bool>> visited;	// visited[i][j]: 방문 체크
	visited.assign(N, std::vector<bool>(M, false));

	std::queue<Coordinate> q;	// q: 좌표를 저장하는 큐

	for(int y=0; y<N; ++y){
		for(int x=0; x<M; ++x){
			if(visited[y][x] == true) {continue;}	// 이미 방문 했다면 continue
			if(MAP[y][x] == 0) {	// 높이가 없는 땅은 산봉우리가 될 수 없음
				visited[y][x] = true;
				continue;
			}

			bool peak = true;	// peak: 산봉우리 여부 -> 주변에 더 높은 땅이 있다면 산봉우리가 될 수 없음
			
			int currHeight = MAP[y][x];	// currHeight: 탐색을 시작하는 위치
			q.push({y, x});
			visited[y][x] = true;

			while(!q.empty()){
				Coordinate curr = q.front();	// curr: 현재 좌표
				q.pop();

				for(int dir=0; dir<8; ++dir){	// 8 방향으로 탐색
					Coordinate next = {curr.y + dirY[dir], curr.x + dirX[dir]};	// next: 다음 좌표

					if(next.y < 0 || next.x < 0 || next.y >= N || next.x >= M) {continue;}	// 범위 벗어나면 continue					
					if(MAP[next.y][next.x] > currHeight) {	// 주변에 현재 땅보다 높은 땅이 있다면
						peak = false;	// 산봉우리가 될 수 없음
						continue;
					}
					if(visited[next.y][next.x] == true) {continue;}	// 이미 방문 한 곳이면 continue
					if(MAP[next.y][next.x] != currHeight) {continue;}	// 다른 높이의 땅이면 continue

					q.push(next);
					visited[next.y][next.x] = true;
				}
			}
			if(peak) {++answer;}	// 봉우리라면 ++answer
		}
	}

	return;
}

void Input(){

	std::cin >> N >> M;

	MAP.assign(N, std::vector<int>(M, 0));

	for(int y=0; y<N; ++y){
		for(int x=0; x<M; ++x){
			std::cin >> MAP[y][x];
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