#include <iostream>
#include <vector>
#include <string>
#include <queue>

int W, H;	// W: 빌딩 지도의 너비, H: 빌딩 지도의 높이
std::vector<std::vector<int>> MAP;	// MAP[i][j]: i 행 j 열의 빌딩 지도 -> -1: 벽이나 불, 0: 빈 공간
std::vector<std::vector<int>> visited;	// visited[i][j]: i 행 j 열의 상근이의 도착 시간

struct Coordinate {	// Coordinate: 좌표
	int y, x;	// y, x: 좌표

	// 방향 벡터
	inline static int dirY[4] = {0, 1, 0, -1};
	inline static int dirX[4] = {1, 0, -1, 0};

	// 동서남북으로 퍼지거나 이동
	static Coordinate nextCoordinate(Coordinate curr, int dir) {
		return {curr.y + dirY[dir], curr.x + dirX[dir]};
	}

	static bool vaildChk(Coordinate next) {	// next: 다음 좌표

		if(next.y < 0 || next.x < 0 || next.y >= H || next.x >= W) return false;	// 지도의 범위 벗어나면 false

		if(MAP[next.y][next.x] == -1) return false;	// 이미 불이 번졌거나, 벽이 있는 곳은 false

		return true;	// 다른 모든 경우에 true
	}

	static bool visitedChk(Coordinate next) {	// next: 다음 좌표
		if(visited[next.y][next.x] == 0) return false;	// 상근이가 움직일 수 있는 곳이라면 true

		return true;
	}

	static bool escapeChk(Coordinate coordi) {	// coordi: 상근이의 좌표
		
		// 탈출할 수 있으면 true
		if(coordi.y == 0) return true;
		if(coordi.y == H - 1) return true;
		if(coordi.x == 0) return true;
		if(coordi.x == W - 1) return true;

		return false;
	}
};

std::queue<Coordinate> personQ, fireQ;	// personQ: 상근이의 좌표 큐, fireQ: 불의 좌표 큐

void solution() {

	if(Coordinate::escapeChk(personQ.front())) {	// 상근이가 빌딩을 탈출한 경우
		std::cout << visited[personQ.front().y][personQ.front().x];	// 가장 빠른 시간 출력
		return;
	}
	
	while(!personQ.empty()) {	// 상근이가 더 이상 움직일 수 없을 때 까지
		int fireQSize = fireQ.size();	// fireQSize: 이번 턴에 불이 번지는 수

		for(int i=0; i<fireQSize; ++i) {
			Coordinate currFire = fireQ.front();	// currFire: 불의 위치
			fireQ.pop();

			for(int dir=0; dir<4; ++dir) {	// 4방향으로 불이 퍼져나감
				Coordinate nextFire = Coordinate::nextCoordinate(currFire, dir);	// nextFire: 다음 불의 위치

				if(!Coordinate::vaildChk(nextFire)) continue;	// 불이 퍼질 수 없으면 continue

				MAP[nextFire.y][nextFire.x] = -1;	// 불 퍼짐

				fireQ.push(nextFire);	// 다음턴에 불이 퍼지기 위해 큐에 넣음
			}
		}

		int personQSize = personQ.size();	// 이번 턴에 움직이는 상근이의 수

		for(int i=0; i<personQSize; ++i) {
			Coordinate currPerson = personQ.front();	// currPerson: 이번 턴에 상근이가 움직이는 수
			personQ.pop();

			for(int dir=0; dir<4; ++dir) {
				Coordinate nextPerson = Coordinate::nextCoordinate(currPerson, dir);	// nextPerson: 상근이의 위치

				if(!Coordinate::vaildChk(nextPerson)) continue;	// 상근이가 갈 수 없는 곳이면 continue
				if(Coordinate::visitedChk(nextPerson)) continue;	// 이미 상근이가 방문했던 곳이면 continue

				visited[nextPerson.y][nextPerson.x] = visited[currPerson.y][currPerson.x] + 1;	// 시간 정보 입력

				if(Coordinate::escapeChk(nextPerson)) {	// 상근이가 빌딩을 탈출한 경우
					std::cout << visited[nextPerson.y][nextPerson.x];	// 가장 빠른 시간 출력
					return;
				}

				personQ.push(nextPerson);
			}
		}
	}

	std::cout << "IMPOSSIBLE";	// 상근이가 빌딩을 탈출할 수 없는 경우

	return;
}

void input() {

	std::cin >> W >> H;

	MAP.assign(H, std::vector<int>(W, 0));	// 빌딩 지도 초기화
	visited.assign(H, std::vector<int>(W, 0));	// 상근이의 위치 초기화

	// 큐 초기화
	personQ = std::queue<Coordinate>();
	fireQ = std::queue<Coordinate>();

	for(int j=0; j<H; ++j) {
		std::string s;	// s: 건물 지도 한 행의 정보
		std::cin >> s;
		for(int i=0; i<W; ++i) {
			if(s[i] == '.') MAP[j][i] = 0;	// 빈 공간
			else if(s[i] == '#') MAP[j][i] = -1;	// 벽
			else if(s[i] == '@') {	// 상근이의 시작 위치
				visited[j][i] = 1;
				personQ.push({j, i});
			}
			else if(s[i] == '*') {	// 불
				MAP[j][i] = -1;	// 불도 벽과 같은 -1을 사용
				fireQ.push({j, i});	// 불은 동서남북 방향으로 인접한 빈 공간으로 퍼짐
			}
		}
	}

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int T;	// T: 테스트 케이스의 수
	std::cin >> T;

	for(int tc=0; tc<T; ++tc) {
		input();

		solution();

		std::cout << '\n';
	}

	return 0;
}