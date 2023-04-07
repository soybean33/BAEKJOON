#include <iostream>
#include <cstring>
#include <algorithm>

struct Fish {
	int num;        // num: 물고기의 번호
	int dir;        // dir: 물고기의 방향
};

struct Shark {
	int y, x;       // y, x: 상어의 좌표
	int dir;        // dir: 상어의 방향
};

Fish MAP[4][4]; // MAP[i][j]: i행 j열의 물고기 정보
Shark shark;    // shark: 상어 정보
int ans;        // ans: 상어가 먹을 수 있는 물고기 번호의 합의 최댓값

// 방향 벡터 -> 12시 방향부터 반시계
int dirY[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dirX[] = { 0, -1, -1, -1, 0, 1, 1, 1 };

void DFS(int eat) {     // eat: 지금 까지 먹은 물고기 번호의 합

	ans = std::max(ans, eat);       // 먹은 물고기 번호의 합의 최대값 갱신

	Fish beforMoveMap[4][4];        // beforMoveMap[i][j]: 물고기가 이동하기 전의 물고기 정보
	memcpy(beforMoveMap, MAP, sizeof(MAP)); // 북구를 위해 복사

	// 물고기 이동
	for (int n = 1; n <= 16; n++) { // 번호가 작은 물고기부터 순서대로 이동
		int fishNum = n;        // fishNum: 물고기 번호
		int flag = 0;   // flag: fishNum을 갖는 물고기 발견하면 1
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 4; i++) {
				if (MAP[j][i].num != fishNum) continue; // 찾는 물고기 번호가 아니면 continue

				Fish cur = MAP[j][i];   // cur: 움직일 불고기
				int curY = j;   // curY: 물고기의 y좌표
				int curX = i;   // curX: 물고기의 x좌표
				int curDir = cur.dir;   // curDir: 물고기의 이동 방향

				for (int dir = 0; dir < 8; dir++) {
                                        int nextDir = (curDir + dir) % 8;       // nextDir: 다음 이동 방향 -> 이동할 수 있을 때 까지 반시계 방향으로 움직임
					int nextY = curY + dirY[nextDir];       // nextY: 다음 이동 y 좌표
					int nextX = curX + dirX[nextDir];       // nextX: 다음 이동 x 좌표

					if (nextY < 0 || nextX < 0 || nextY >= 4 || nextX >= 4) continue;       // 범위 밖으로 나가면 continue
					if (MAP[nextY][nextX].num == -1) continue;      // 상어가 있는 칸이면 continue

					flag = 1;       // 이동 할 수 있는 칸 발견
                                        MAP[curY][curX].dir = nextDir;  // 이동 방향 갱신

					Fish nextFish = MAP[nextY][nextX];      // nextFish: 이동할 칸에 있는 물고기 -> 빈 칸이여도 상관 없음
					MAP[nextY][nextX] = MAP[curY][curX];    
					MAP[curY][curX] = nextFish;
					break;  // 물고기를 찾았고 위치를 변경하였으므로 다음 물고기 탐색
				}
				if (flag == 1) break;
			}
			if (flag == 1) break;
		}
	}

	Fish afterMoveMap[4][4];        // afterMoveMap[i][j]: 물고기가 이동하고 나서의 물고기 정보
	Shark saveShark = shark;        // saveShark: 물고기를 먹기 전의 상어 위치
	memcpy(afterMoveMap, MAP, sizeof(MAP)); // 복구를 위해 복사

	// 상어 이동
	for (int i = 1; i < 4; i++) {
		int nextY = shark.y + (dirY[shark.dir]) * i;    // nextY: 다음 상어 y 위치
		int nextX = shark.x + (dirX[shark.dir]) * i;    // nextX: 다음 상어 x 좌표

		if (nextY < 0 || nextX < 0 || nextY >= 4 || nextX >= 4) break;  // 범위 밖으로 나가면 더 이상 탐색 하지 않아도 되므로 break
		if (MAP[nextY][nextX].num == 0) continue;       // 물고기가 없는 빈 칸이면 continue

		Fish eatFish = MAP[nextY][nextX];       // eatFish: 상어가 먹을 수 있는 물고기 발견		

		MAP[shark.y][shark.x].num = 0;  // 물고기 먹음 -> 빈칸으로 표시

		shark.y = nextY;        // 상어 이동
		shark.x = nextX;
		MAP[nextY][nextX].num = -1;     // 상어 위치 표시

		shark.dir = eatFish.dir;        // 상어는 먹은 물고기의 방향을 갖음
		
		DFS(eat + eatFish.num); // 먹은 물고기 번호 합

		shark = saveShark;      // 상어 위치 복구

		memcpy(MAP, afterMoveMap, sizeof(MAP)); // 상어가 움직이기 전으로 복구
	}

	memcpy(MAP, beforMoveMap, sizeof(MAP)); // 물고기가 움직이기 전으로 복구

	return;
}

void sol() {
	shark = { 0, 0, MAP[0][0].dir };        // 청소년 상어는 (0, 0)의 물고기를 먹고 그 공간에 들어가며, 먹은 물고기의 방향을 갖음

	int firstEat = MAP[0][0].num;   // firstEat: 첫 번째로 먹은 물고기 번호
	MAP[0][0].num = -1;     // 상어의 위치는 -1로 표시

	DFS(firstEat);

	return;
}

void input() {
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			int num, dir;   // num: 물고기 번호, dir: 물고기 방향
			std::cin >> num >> dir;
			dir--;  // 주어진 방향 1 ~ 8을 0 ~ 7로 사용
			MAP[j][i] = { num, dir };
		}
	}

	return;
}

int main() {
	input();
	sol();

	std::cout << ans;
	return 0;
}

