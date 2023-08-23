#include <iostream>
#include <vector>
#include <string>
#include <queue>

int N, M;	// N: 미로의 세로 길이, M: 미로의 가로 길이

struct Coordinate {	// 좌표
	int y, x;	// y, x: 좌표 값

	// 방향 벡터
	inline static const int dirY[4] = {0, 1, 0, -1};
	inline static const int dirX[4] = {-1, 0, 1, 0};

	// 다음 좌표
	static Coordinate NextCoordinate(Coordinate curr, int dir) {	// curr: 현재 좌표, dir: 이동 방향
		return {curr.y + dirY[dir], curr.x + dirX[dir]};
	}

	// 미로를 벗어나면 true
	static bool OutOfBound(Coordinate next) {	// next: 다음 좌표	
		if(next.y < 0 || next.x < 0 || next.y >= N || next.x >= M) return true;	// 미로의 범위를 벗어나면 true
		return false;
	}
};

std::vector<std::vector<int>> MAP;	// MAP[i][j]: i 행 j 열의 미로 정보 -> .: 지나갈 수 있는 길, +: 지나갈 수 없는 벽
std::vector<std::vector<char>> ans;	// ans[i][j]: i 행 j 열의 미로 정답 -> .: 지나갈 수 있는 길, +: 지나갈 수 없는 벽, @: 지나가지 않은 길

Coordinate start{-1, -1}, end{-1, -1};	// start: 미로 시작 지점, end: 미로 끝 지점

void Solution() {

	std::vector<std::vector<bool>> visited;	// visited[i][j]: i 행 j 열 방문 여부, 방문 했다면 true
	std::vector<std::vector<Coordinate>> path;	// path[i][j]: i 행 j 열에 도착하기 위해 출발한 칸의 좌표

	visited.assign(N, std::vector<bool>(M, false));	// visited false로 초기화
	path.assign(N, std::vector<Coordinate>(M, {-1, -1}));	// 경로 정보 {-1, -1}로 초기화

	std::queue<Coordinate> q;	// q: 탐색 칸 저장

	q.push(start);
	visited[start.y][start.x] = true;

	while(!q.empty()) {
		Coordinate curr = q.front();	// curr: 현재 위치하고 있는 미로의 칸
		q.pop();

		for(int dir=0; dir<4; ++dir) {
			Coordinate next = Coordinate::NextCoordinate(curr, dir);	// next: 다음 칸

			if(Coordinate::OutOfBound(next)) continue;	// 미로 범위 벗어나면 continue
			if(MAP[next.y][next.x] == -1) continue;	// 지나갈 수 없는 벽이라면 continue
			if(visited[next.y][next.x]) continue;	// 이미 방문한 칸이라면 continue

			visited[next.y][next.x] = true;	// 방분 체크
			path[next.y][next.x] = curr;	// 경로 저장

			if(next.y == end.y && next.x == end.x) {break;}	// 탈출 성공했다면 break

			q.push(next);
		}
	}

	ans.assign(N, std::vector<char>(M, '.'));	// 정답 초기화

	for(int j=0; j<N; ++j) {
		for(int i=0; i<M; ++i) {
			if(MAP[j][i] == -1) {ans[j][i] = '+';}	// 벽
			else {ans[j][i] = '@';}	// 지나가지 않은 칸
		}
	}

	Coordinate search = end;	// search: 경로를 역으로 탐색
	while(search.y != -1) {
		ans[search.y][search.x] = '.';	// 지나간 길은 .로 표시

		search = path[search.y][search.x];	// 다음 탐색을 위하여 값 갱신
	}

	return;
}

void Input() {

	std::cin >> N >> M;

	MAP.assign(N, std::vector<int>(M, 0));	// 지도 공간 할당

	for(int j=0; j<N; ++j) {
		std::string s;	// s: 미로 한 행의 정보
		std::cin >> s;

		for(int i=0; i<M; ++i) {
			if(s[i] == '+') {MAP[j][i] = -1;}	// 지나갈 수 없는 벽의 값 -1
			else {	// 지나갈 수 있는 길의 경우
				if(j == 0 || j == N-1 || i == 0 || i == M-1) {	// 미로의 가장자리에 존재하는 미로의 구멍
					if(start.y == -1) {start = {j, i};}	// 미로의 시작 지점 저장
					else {end = {j, i};}	// 시작 지점이 정해졌다면, 끝 지점 저장
				}
			}
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

	for(int j=0; j<N; ++j) {
		for(int i=0; i<M; ++i) {
			std::cout << ans[j][i];
		}
		std::cout << '\n';
	}

	return 0;
}