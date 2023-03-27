#include <iostream>
#include <cstring>
#include <queue>

struct Coordinate {
	int y, x;
};

int N, M, K;	// N: 지도의 세로 크기, M: 지도의 가로 크기, K: 이동하는 횟수
int MAP[22][22];	// MAP[i][j]: 지도의 i행 j열의 값
int dic[6] = { 1, 2, 3, 4, 5, 6 };	// dic[i]: 주사위의 숫자
int y = 1, x = 1;	// y, x: 주사위 위치
int ans;	// ans: 점수의 합

// 동, 남, 서, 북
int dir;	// dir: 현재 방향
int dirY[] = { 0, 1, 0, -1 };
int dirX[] = { 1, 0, -1, 0 };

int score(int s) {
	int cnt = 1;	// cnt: 연속된 같은 수의 수 -> 자기 자신 1 초기값
	int visited[22][22] = { 0, };	// visited[i][j]: i행 j열 확인
	std::queue<Coordinate> q;	// q: queue
	q.push({ y, x });
	visited[y][x] = 1;

	while (!q.empty()) {
		Coordinate now = q.front();
		q.pop();

		for (int d = 0; d < 4; d++) {
			// newY, newX: 확인할 위치
			int newY = now.y + dirY[d];
			int newX = now.x + dirX[d];

			if (MAP[newY][newX] != s) continue;	// 숫자 다르면 continue
			if (visited[newY][newX] == 1) continue;	// 범위 벗나면 continue

			visited[newY][newX] = 1;
			cnt++;

			q.push({ newY, newX });
		}
	}

	return cnt;
}

void roll(int d) {
	int newDic[6] = { 0, };
	if (d == 0) {	// 동
		newDic[0] = dic[3];
		newDic[1] = dic[1];
		newDic[2] = dic[0];
		newDic[3] = dic[5];
		newDic[4] = dic[4];
		newDic[5] = dic[2];
	}
	else if (d == 1) {	// 남
		newDic[0] = dic[1];
		newDic[1] = dic[5];
		newDic[2] = dic[2];
		newDic[3] = dic[3];
		newDic[4] = dic[0];
		newDic[5] = dic[4];
	}
	else if (d == 2) {	// 서
		newDic[0] = dic[2];
		newDic[1] = dic[1];
		newDic[2] = dic[5];
		newDic[3] = dic[0];
		newDic[4] = dic[4];
		newDic[5] = dic[3];
	}
	else if (d == 3) {	// 북
		newDic[0] = dic[4];
		newDic[1] = dic[0];
		newDic[2] = dic[2];
		newDic[3] = dic[3];
		newDic[4] = dic[5];
		newDic[5] = dic[1];
	}

	for (int i = 0; i < 6; i++) {
		dic[i] = newDic[i];
	}

	return;
}

void sol() {
	while (K > 0) {
		// newY, newX: 새로운 주사위 위치
		int newY = y + dirY[dir];
		int newX = x + dirX[dir];

		// 벽을 만나면 -> 이동 방향을 반대로 한 다음 한 칸 굴러감
		if (MAP[newY][newX] == -1) {
			dir = (dir + 2) % 4;
			newY = y + dirY[dir];
			newX = x + dirX[dir];
		}

		// 주사위 이동
		y = newY;
		x = newX;
		roll(dir);

		int s = score(MAP[newY][newX]);	// s: 점수 = (y, x)의 점수 * 연속한 같은 수의 수

		ans += MAP[newY][newX] * s;	// 점수 합산

		if (dic[5] > MAP[newY][newX]) {	// A > B인 경우 이동 방향을 90도 시계 방향으로 회전
			dir = (dir + 1) % 4;
		}
		else if (dic[5] < MAP[newY][newX]) {	// A < B인 경우 이동 방향을 90도 반시계 방향으로 회전
			dir = (dir - 1 + 4) % 4;
		}

		K--;	// 이동하는 횟수 감소
	}

}

void input() {
	memset(MAP, -1, sizeof(MAP));	// MAP 외부는 -1로 처리
	std::cin >> N >> M >> K;
	for (int j = 1; j <= N; j++) {
		for (int i = 1; i <= M; i++) {
			std::cin >> MAP[j][i];
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