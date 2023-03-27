#include <iostream>
#include <cstring>

struct Change {
	int len;
	int cnt;
};

int N;	// N: 격자의 한 변의 길이
int A[530][530];	// A[i][j]: i행 j열의 모래의 양
constexpr int OFFSET = 10;	// OFFSET: 격자 밖
int ans = 0;	// ans: 격자의 밖으로 나간 모래의 양
Change change = { 1, 0 };	// change: 바람의 방향 변화

// 방향 벡터: 좌 하 우 상
int dir;	// 현재 방향
int dirY[] = { 0, 1, 0, -1 };
int dirX[] = { -1, 0, 1, 0 };

float wind[5][5] = {	// wind[i][j]: i행 j열의 흩날리는 모래의 양
	{0, 0, 0.02, 0, 0},
	{0, 0.1, 0.07, 0.01, 0},
	{0.05, 0, 0, 0, 0},
	{0, 0.1, 0.07, 0.01, 0},
	{0, 0, 0.02, 0, 0}
};

void turn() {	// 흩날리는 모래 비율 반시계 회전
	float tmpWind[5][5] = { 0, };	// tmpWind: 흩날리는 모래 비율 임시 저장

	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 5; i++) {
			tmpWind[4 - i][j] = wind[j][i];
		}
	}

	memcpy(wind, tmpWind, sizeof(wind));

	return;
}

void sol() {
	int y = N / 2 + OFFSET, x = N / 2 + OFFSET;	// y, x: 토네이도 위치
	int len = 0;	// len: 토네이도 길이

	while (true) {
		if (y == OFFSET && x == OFFSET) break;	// (0, 0)까지 이동한 뒤 소멸

		if (change.len == len) {	// 길이 만큼 이동 완료
			if (change.cnt == 1) {	// 2번 방향 전환 했으면 길이 ++
				change.len++;
				change.cnt = 0;				
			}
			else {				
				change.cnt++;
				
			}
			len = 0;
			dir = (dir + 1) % 4;	// 반 시계 방향으로 회전
			turn();
		}
		len++;
		
		y = y + dirY[dir];
		x = x + dirX[dir];
		float sand = (float)(A[y][x]);	// sand: 흩날릴 모래의 총 양
		int blow = 0;	// blow: 흩날린 모래

		for (int j = -2; j <= 2; j++) {
			for (int i = -2; i <= 2; i++) {
				// windY, windX: 흩날리는 모래 방향
				int windY = y + j;
				int windX = x + i;
				
				A[windY][windX] += (int)(sand * wind[j + 2][i + 2]);
				blow += (int)(sand * wind[j + 2][i + 2]);
			}
		}
		A[y + dirY[dir]][x + dirX[dir]] += sand - blow;	// 흩날릴 총 모래의 양 - 흩날린 모래
		A[y][x] = 0;		
	}
	for (int j = 0; j < N + 2 * OFFSET; j++) {
		for (int i = 0; i < N + 2 * OFFSET; i++) {
			if (j >= OFFSET && i >= OFFSET && j < N + OFFSET && i < N + OFFSET) continue;	// 격자 범위 안쪽 모래 continue
			ans += A[j][i];	// 격자 밖 모래 더하기
		}
	}

	return;
}

void input() {
	std::cin >> N;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			std::cin >> A[j + OFFSET][i + OFFSET];
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