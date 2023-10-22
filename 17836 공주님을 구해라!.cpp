#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

constexpr int INF = 21e8;	// INF: 나올 수 없는 값

// 방향 벡터
constexpr int dirY[4] = {0, 1, 0, -1};
constexpr int dirX[4] = {1, 0, -1, 0};

struct Coordinate{	// 좌표
	int y, x;
};

struct Hero{	// 영웅 정보
	Coordinate coordi;	// coordi: 좌표
	bool sword;	// sword: 전설의 명검 "그람"의 소유 여부
};

int N, M, T;	// N: 성의 세로 크기, M: 성의 가로 크기, T: 공주에게 걸린 저주의 제한 시간
std::vector<std::vector<int>> MAP;	// MAP[i][j]: i 행 j 열의 정보 -> 0 빈공간, 1 마법의 벽, 2 그람이 놓여있는 공간

int answer;	// answer: 용사가 공주님에게 도달할 수 있는 최단 시간

void Solution(){

	std::vector<std::vector<std::vector<int>>> visited;	// visited[i][j][k]: 용사가 i 행 j 열에 도달할 수 있는 최단 시간 -> k 가 0 이면 그람을 소지한 상태, 1 이면 그람이 없는 상태
	visited.assign(N, std::vector<std::vector<int>>(M, std::vector<int>(2, INF)));	// 나올 수 없는 값으로 초기화

	std::queue<Hero> q;	// q: 현재 위치를 저장할 큐

	q.push({{0, 0}, false});
	visited[0][0][0] = 0;	// 시작 위치는 (0, 0)에서 전설의 명검 "그람"을 가지고 있지 않은 상태

	while(!q.empty()){
		Hero curr = q.front();	// curr: 현재 용사의 상태
		q.pop();

		for(int dir=0; dir<4; ++dir){	// 4가지 방향으로 탐색
			Hero next = {{curr.coordi.y + dirY[dir], curr.coordi.x + dirX[dir]}, curr.sword};	// next: 다음의 용사의 상태

			if(next.coordi.y < 0 || next.coordi.x < 0 || next.coordi.y >= N || next.coordi.x >= M) {continue;}	// 성 밖으로 나가면 continue

			if(curr.sword == true) {	// 전설의 명검 "그람"이 있는 상태
				int time = visited[curr.coordi.y][curr.coordi.x][1] + 1;	// time: 다음 좌표로 이동할 때 소요되는 시간
				if(time > T) {continue;}	// 공주에게 걸린 저주의 제한 시간보다 크다면 continue

				if(visited[next.coordi.y][next.coordi.x][1] <= time) {continue;}	// 이미 더 적은 시간으로 방문 했었다면 continue

				q.push(next);
				visited[next.coordi.y][next.coordi.x][1] = time;
			}
			else{	// 전설의 명검 "그람"이 없는 상태
				if(MAP[next.coordi.y][next.coordi.x] == 1) {continue;}	// 마법의 벽을 통과할 수 없음
				if(MAP[next.coordi.y][next.coordi.x] == 2) {next.sword = true;}	// 전설의 명검 "그람"을 찾음

				int time = visited[curr.coordi.y][curr.coordi.x][0] + 1;	// time: 다음 좌표로 이동할 때 소요되는 시간
				if(time > T) {continue;}	// 공주에게 걸린 저주의 제한 시간보다 크다면 continue

				if(visited[next.coordi.y][next.coordi.x][0] <= time) {continue;}	// 이미 더 적은 시간으로 방문 했었다면 continue

				q.push(next);
				if(next.sword == true) {visited[next.coordi.y][next.coordi.x][1] = time;}	// 전설의 명검 "그람"을 찾은 경우
				else {visited[next.coordi.y][next.coordi.x][0] = time;}	// 전설의 명검 "그람"을 아직 찾지 못한 경우				
			}
		}
	}


	answer = std::min(visited[N-1][M-1][0], visited[N-1][M-1][1]);	// 전설의 명검 "그람"을 찾았을 때와 찾지 못하였을 경우의 최단 시간 비교

	return;
}

void Input(){

	std::cin >> N >> M >> T;

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

	if(answer == INF) {std::cout << "Fail";}	// T시간 내에 공주님이 있는 곳에 도달하지 못함
	else std::cout << answer;	// 용사가 공주님에게 도달할 수 있는 최단 시간

	return 0;
}