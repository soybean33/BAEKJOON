#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

struct Coordinate {
	int y, x;
};

int N, M;	// N: 세로 크기, M: 가로 크기
int MAP[10][10];	// MAP[i][j]: i행 j열의 정보
int watch[10][10];	// watch[i][j]: i행 j열의 감시 정보, 값이 0이면 사각지대
int num;	// num: CCTV의 개수
int ans = 21e8;	// ans: 사각 지대의 최소 값
std::vector<Coordinate> v;	// v: cctv 정보 저장

// 방향 벡터 ->	상 우 하 좌
int dirY[] = { -1, 0, 1, 0 };
int dirX[] = { 0, 1, 0, -1 };

int dirNum[] = { 0, 4, 2, 4, 4, 1 };	// dirNum[i]: i cctv의 감시 종류 수

void fill(int j, int i, int dir, int n) {

	int y = j;
	int x = i;

	while (true) {
		if (y < 0 || x < 0 || y >= N || x >= M) return;
		if (MAP[y][x] == -1) return;

		watch[y][x] += n;

		y += dirY[dir];
		x += dirX[dir];
	}

	return;
}

void DFS(int depth) {

	if (depth == num) {	// 모든 cctv에 대하여 시도 해봄
		int cnt = 0;
		for (int j = 0; j < N; j++) {
			for (int i = 0; i < M; i++) {
				if (watch[j][i] == 0)	// 사각지대 수 count
					cnt++;
			}
		}

		ans = std::min(ans, cnt);
		return;
	}


	int j = v[depth].y;
	int i = v[depth].x;

	int cctvNum = MAP[j][i];

	for (int dir = 0; dir < dirNum[cctvNum]; dir++) {
		if (cctvNum == 1) {	// cctv가 1인 경우 -> 4 번 1개의 가지
			fill(j, i, dir % 4, 1);
		}
		if (cctvNum == 2) {	// cctv가 2인 경우 -> 2 번 2개의 가지
			fill(j, i, dir % 4, 1);
			fill(j, i, (dir + 2) % 4, 1);
		}
		if (cctvNum == 3) {	// cctv가 3인 경우 -> 4 번 2개의 가지
			fill(j, i, dir % 4, 1);
			fill(j, i, (dir + 1) % 4, 1);
		}
		if (cctvNum == 4) {	// cctv가 4인 경우 -> 4 번 3개의 가지
			fill(j, i, dir % 4, 1);
			fill(j, i, (dir + 1) % 4, 1);
			fill(j, i, (dir + 2) % 4, 1);
		}
		if (cctvNum == 5) {	// cctv가 5인 경우 -> 1 번 4개의 가지
			fill(j, i, dir % 4, 1);
			fill(j, i, (dir + 1) % 4, 1);
			fill(j, i, (dir + 2) % 4, 1);
			fill(j, i, (dir + 3) % 4, 1);
		}

		DFS(depth + 1);

		if (cctvNum == 1) {
			fill(j, i, dir % 4, -1);
		}
		if (cctvNum == 2) {
			fill(j, i, dir % 4, -1);
			fill(j, i, (dir + 2) % 4, -1);
		}
		if (cctvNum == 3) {
			fill(j, i, dir % 4, -1);
			fill(j, i, (dir + 1) % 4, -1);
		}
		if (cctvNum == 4) {
			fill(j, i, dir % 4, -1);
			fill(j, i, (dir + 1) % 4, -1);
			fill(j, i, (dir + 2) % 4, -1);
		}
		if (cctvNum == 5) {
			fill(j, i, dir % 4, -1);
			fill(j, i, (dir + 1) % 4, -1);
			fill(j, i, (dir + 2) % 4, -1);
			fill(j, i, (dir + 3) % 4, -1);
		}
	}

}

void sol() {
	DFS(0);

	return;
}


void input() {
	std::cin >> N >> M;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++) {
			std::cin >> MAP[j][i];
			if (MAP[j][i] == 6) {	// 벽인 경우
				MAP[j][i] = -1;	// MAP[j][i]를 -1로 재설정
				watch[j][i] = 100;	// 사각지대가 될 수 없으므로 100으로 처리
			}
			if (MAP[j][i] != 0 && MAP[j][i] != -1) {	// cctv인 경우 -> 0도 아니고 -1도 아니고
				v.push_back({ j, i });	// cctv 추가
				num++;	// cctv 개수 증가
				watch[j][i] = 100;	// 사각지대가 될 수 없으므로 100으로 처리
			}
		}
	}

	return;
}


void reset() {
	memset(MAP, -1, sizeof(MAP));	// 처음 모두 -1로 초기화

	return;
}

int main() {
	reset();
	input();
	sol();
	std::cout << ans << std::endl;
	return 0;
}