#include <iostream>
#include <vector>
#include <algorithm>

// 방향 벡터 -> 오른쪽, 아래, 왼쪽, 위
constexpr int dirY[4] = {0, 1, 0, -1};
constexpr int dirX[4] = {1, 0, -1, 0};

struct Coordinate {
	int y, x;

	static Coordinate nextCoordi(Coordinate& curr, int& dir) {	// curr 위치로 옮겨올 위치 return
		return {curr.y + dirY[dir], curr.x + dirX[dir]};
	}
};

std::vector<std::vector<int>> Solution(const int& N, const int& M, const int& R, std::vector<std::vector<int>>& MAP) {

	int half = std::min(N, M) / 2;	// half: 회전 시켜야 할 단위의 수
	Coordinate start = {0, 0};	// start: 회전 시작 위치

	for(int rotate=0; rotate<half; ++rotate) {
		int yLen = N - (rotate * 2);	// yLen: 회전 단위의 세로 길이
		int xLen = M - (rotate * 2);	// xLen: 회전 단위의 가로 길이

		int rotateNum = R % (2 * xLen + 2 * yLen - 4);	// rotateNum: 회전의 횟수 -> 단위의 변의 길이 이상은 필요 없음

		while(rotateNum--) {
			Coordinate curr = start;	// curr: 현재 회전 위치
			int startPointNum = MAP[start.y][start.x];	// startPointNum: 회전 시작 위치의 값 -> 저장하고 있다가 다음에 사용

			for(int dir=0; dir<4; ++dir) {
				int moveNum = dir % 2 == 0 ? xLen - 1 : yLen - 1;	// moveNum: 가로, 세로에 따른 이동 횟수

				for(int move = 0; move < moveNum; ++move) {
					Coordinate next = Coordinate::nextCoordi(curr, dir);	// next: 값을 가져올 좌표

					MAP[curr.y][curr.x] = MAP[next.y][next.x];	// 값 이동

					curr = next;	// 다음 좌표로 갱신
				}
			}

			MAP[start.y + 1][start.x] = startPointNum;	// 저장해둔 시작 위치의 값 넣음
		}

		start = {start.y + 1, start.x + 1};	// 다음 단위로 시작 위치 변경
	}

	return MAP;
}

void Input(int& N, int& M, int& R, std::vector<std::vector<int>>& MAP) {

	std::cin >> N >> M >> R;

	MAP.assign(N, std::vector<int>(M, 0));

	for(int y=0; y<N; ++y) {
		for(int x=0; x<M; ++x) {
			std::cin >> MAP[y][x];
		}
	}

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M, R;	// N: 배열의 세로 크기 2<=N<=300, M: 배열의 가로 크기 2<=M<=300, R: 회전의 수 1<=R<=1,000
	std::vector<std::vector<int>> MAP;	// MAP[i][j]: i 행 j 열의 값 1<=MAP[i][j]<=10^8

	Input(N, M, R, MAP);

	Solution(N, M, R, MAP);

	for(int y=0; y<N; ++y) {
		for(int x=0; x<M; ++x) {
			std::cout << MAP[y][x] << ' ';
		}
		std::cout << '\n';
	}

	return 0;
}