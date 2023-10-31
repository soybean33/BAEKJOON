#include <iostream>
#include <vector>

// 방향벡터 -> 우 하 좌 상
constexpr int dirY[4] = { 0, 1, 0, -1 };
constexpr int dirX[4] = { 1, 0, -1, 0 };

struct Coordinate {	// Coordinate: 좌표
	int y, x;
};

struct Robot {	// Robot: 로봇의 정보
	Coordinate coordi;	// coordi: 좌표
	int dir;	// dir: 방향
};

struct Order {	// Order: 명령
	int num;	// num: 움직이는 로봇 번호
	char type;	// type: 명령의 타입 -> L: 반시계 회전, R: 시계 회전, F: 전진
	int repeat;	// repeat: 반복 횟수
};

int A, B;	// A: 가로 크기, B: 세로 크기
std::vector<std::vector<int>> MAP;	// MAP[i][j]: i 행 j 열의 존재하는 로봇 번호
int N, M;	// N: 로봇의 수, M: 명령의 수

std::vector<Robot> robots;	// robots[i]: i 번 로봇의 정보
std::vector<Order> orders;	// orders[i]: i 번째 명령

int flag;	// flag: 안정성 검증 -> 0: 문제가 없음, 1: 벽에 충돌, 2: 다른 로봇에 충돌
int robotNum;	// robotNum: 충돌한 로봇 번호
int crashRobotNum;	// crashRobotNum: robotNum 로봇에 충돌한 로봇

void Solution() {

	for (const Order& order : orders) {	// order: 실행할 명령
		Robot curr = robots[order.num];	// curr: 명령을 받은 로봇

		if (order.type == 'L') {	// 반시계 회전 명령
			int repeat = order.repeat % 4;	// repeat: 반복 횟수

			for (int i = 0; i < repeat; ++i) {
				curr.dir = (curr.dir - 1 + 4) % 4;	// 반시계 회전
			}
			robots[order.num].dir = curr.dir;
		}
		else if (order.type == 'R') {	// 시계 회전 명령
			int repeat = order.repeat % 4;	// repeat: 반복 횟수

			for (int i = 0; i < repeat; ++i) {
				curr.dir = (curr.dir + 1) % 4;	// 시계 회전
			}
			robots[order.num].dir = curr.dir;
		}
		else {	// 직진 명령
			MAP[curr.coordi.y][curr.coordi.x] = 0;	// 원래 있던 곳 0으로 초기화

			int repeat = order.repeat;	// repeat: 반복 횟수

			for (int i = 0; i < repeat; ++i) {
				curr.coordi = { curr.coordi.y + dirY[curr.dir], curr.coordi.x + dirX[curr.dir] };

				if (curr.coordi.y < 0 || curr.coordi.x < 0 || curr.coordi.y >= B || curr.coordi.x >= A) {	// 벽에 충돌하는 경우
					flag = 1;
					robotNum = order.num;
					return;
				}

				if (MAP[curr.coordi.y][curr.coordi.x] != 0) {	// 다른 로봇에 충돌하는 경우
					flag = 2;
					robotNum = order.num;
					crashRobotNum = MAP[curr.coordi.y][curr.coordi.x];
					return;
				}
			}

			MAP[curr.coordi.y][curr.coordi.x] = order.num; // 로봇 이동 완료
			robots[order.num].coordi = curr.coordi;	// 로봇 정보 갱신
		}
	}

	return;
}

void Input() {

	std::cin >> A >> B;

	MAP.assign(B, std::vector<int>(A, 0));

	std::cin >> N >> M;

	robots.assign(N + 1, { {0, 0}, 0 });

	for (int i = 0; i < N; ++i) {
		int x, y;	// x, y: 좌표
		char dir;	// dir: 방향
		int dirNum = 0;	// dirNum: 방향을 숫자로 변경
		std::cin >> x >> y >> dir;

		// 좌표 계산
		--x;
		y = B - y;

		// 방향 계산
		if (dir == 'E') { dirNum = 0; }
		else if (dir == 'S') { dirNum = 1; }
		else if (dir == 'W') { dirNum = 2; }
		else if (dir == 'N') { dirNum = 3; }

		robots[i + 1] = { {y, x},  dirNum };	// 로봇 정보에 넣음
		MAP[y][x] = i + 1;	// 지도에 넣음
	}

	orders.assign(M, { 0, 0, 0 });

	for (int i = 0; i < M; ++i) {
		std::cin >> orders[i].num >> orders[i].type >> orders[i].repeat;	// 명령 넣음
	}

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();

	if (flag == 0) { std::cout << "OK"; }
	else if (flag == 1) { std::cout << "Robot " << robotNum << " crashes into the wall"; }
	else { std::cout << "Robot " << robotNum << " crashes into robot " << crashRobotNum; }

	return 0;
}