#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

constexpr int INF = 21e8;	// INF: 나올 수 없는 값

struct Coordinate {	// Coordinate: 좌표와 관련된 구조체
	int y, x;	// y, x: 좌표 값

	// 방향 벡터
	inline static const int dirY[4] = {0, 1, 0, -1};
	inline static const int dirX[4] = {1, 0, -1, 0};

	// 작은 좌표
	static Coordinate MinCoordi(Coordinate& leftTop, Coordinate& rightBottom) {
		return {std::min(leftTop.y, rightBottom.y), std::min(leftTop.x, rightBottom.x)};
	}

	// 큰 좌표
	static Coordinate MaxCoordi(Coordinate& leftTop, Coordinate& rightBottom) {
		return {std::max(leftTop.y, rightBottom.y), std::max(leftTop.x, rightBottom.x)};
	}

	// 다음 좌표
	static Coordinate NextCoordi(Coordinate curr, int dir) {
		return {curr.y + dirY[dir], curr.x + dirX[dir]};
	}

	// 범위 벗어나면 true
	static bool OutOfBound(Coordinate& coordi) {

		if(coordi.y < 0) return true;
		if(coordi.x < 0) return true;
		if(coordi.y >= 501) return true;
		if(coordi.y >= 501) return true;

		return false;
	}
};

std::vector<std::vector<int>> MAP;	// MAP[i][j]: i 행 j 열의 정보 -> 0: 안전한 구역, 1: 위험한 구역, 2: 죽음의 구역
std::vector<std::vector<int>> visited;	// visited[i][j]: i 행 j 열의 잃은 생명력 정보

void Solution() {

	std::queue<Coordinate> q;	// q: 세준이의 좌표를 저장하는 큐

	// 시작위치 설정
	q.push({0, 0});
	visited[0][0] = 0;

	while(!q.empty()) {
		Coordinate curr = q.front();	// curr: 현재 위치
		q.pop();

		for(int dir=0; dir<4; ++dir) {
			Coordinate next = Coordinate::NextCoordi(curr, dir);	// next: 다음 위치

			if(Coordinate::OutOfBound(next)) continue;	// 범위 벗어나면 continue
			if(MAP[next.y][next.x] == 2) continue;	// 죽음의 구역에는 갈 수 없으므로 continue

			int nextLoseLife = (MAP[next.y][next.x] == 1) ? visited[curr.y][curr.x] + 1 : visited[curr.y][curr.x];	// nextLoseLife: 다음 위치에서의 세준이가 잃은 생명력

			if(visited[next.y][next.x] <= nextLoseLife) continue;	// 더 많은 생명력을 잃고 해당 위치로 이동한다면 continue

			visited[next.y][next.x] = nextLoseLife;	// 잃은 생명력 기록

			q.push(next);	// 다음 탐색에 사용하기 위하여 큐에 넣음
		}
	}

	return;
}

void Input() {

	int N, M;	// N: 위험한 구역의 수, M: 죽음의 구역의 수

	// 초기화
	MAP.assign(501, std::vector<int>(501, 0));
	visited.assign(501, std::vector<int>(501, INF));

	std::cin >> N;

	for(int i=0; i<N; ++i) {
		Coordinate A, B;	// A, B: 입력되는 위험한 구역 좌표 정보
		
		std::cin >> A.x >> A.y >> B.x >> B.y;

		Coordinate minCoordi = Coordinate::MinCoordi(A, B);	// minCoordi: 작은 좌표
		Coordinate maxCoordi = Coordinate::MaxCoordi(A, B);	// maxCoordi: 큰 좌표

		// 위험 구역 표시
		for(int y=minCoordi.y; y<=maxCoordi.y; ++y) {
			for(int x=minCoordi.x; x<=maxCoordi.x; ++x) {
				MAP[y][x] = 1;	// 위험 구역
			}
		}
	}

	std::cin >> M;

	for(int i=0; i<M; ++i) {
		Coordinate A, B;	// A, B: 입력되는 죽음의 구역 좌표

		std::cin >> A.x >> A.y >> B.x >> B.y;

		Coordinate minCoordi = Coordinate::MinCoordi(A, B);	// minCoordi: 작은 좌표
		Coordinate maxCoordi = Coordinate::MaxCoordi(A, B);	// maxCoordi: 큰 좌표

		// 죽음의 구역 표시
		for(int y=minCoordi.y; y<=maxCoordi.y; ++y) {
			for(int x=minCoordi.x; x<=maxCoordi.x; ++x) {
				MAP[y][x] = 2;	// 죽음의 구역
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

	(visited[500][500] == INF)? (std::cout << -1) : (std::cout << visited[500][500]);	// (500, 500)까지 잃은 생명의 최솟값, 갈 수 없을 때는 -1

	return 0;
}