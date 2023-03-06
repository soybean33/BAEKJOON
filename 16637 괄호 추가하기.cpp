#include <iostream>

int N;
int MAP[17][17];	// MAP[i][j]: i열 j행의 정보
int sy = 0, sx = 0;	// 시작 위치: (0, 0)
int dy, dx;	// 도착 위치: (N-1, N-1)


int dirY[3][3] = { {0,1,0}, {1,1,0}, {0,1,1} };	// 파이프 설치 Y 방향
int dirX[3][3] = { {1,1,0}, {0,1,0}, {1,0,1} };	// 파이프 설치 X 방향

int num[] = { 2, 2, 3 };	// num: 이전 방향에 따른 설치할 수 있는 파이프 수
int ans;	// ans: 정답

void DFS(int curY, int curX, int dir) {

	if (curY == dy && curX == dx) {
		ans++;
		return;
	}
	
	for (int i = 0; i < num[dir]; i++) {
		int newY = curY + dirY[dir][i];	// newY: 다음 y 좌표
		int newX = curX + dirX[dir][i];	// newX: 다음 x 좌표
		int newDir;

		if (newY < 0 || newX < 0 || newY >= N || newX >= N) continue;	// 범위 벗어남
		if (MAP[newY][newX] != 0) continue;	// 벽 있으면 못함
		

		if (dirY[dir][i] == 1 && dirX[dir][i] == 1)
			newDir = 2;
		else if (dirY[dir][i] == 1)
			newDir = 1;
		else
			newDir = 0;

		// 대각선 파이프의 경우 3칸의 칸이 비어있어야 설치 가능함
		if (dir == 0 || dir == 1) {
			if (i == 1) {
				if (MAP[newY-1][newX] == 1 || MAP[newY][newX-1] == 1) continue;
			}
		}
		else {
			if (i == 2) {
				if (MAP[newY - 1][newX] == 1 || MAP[newY][newX - 1] == 1) continue;
			}
		}

		DFS(newY, newX, newDir);		
	}

	return;
}

void sol() {

	int dir = 0;	// 처음 설치되어 있는 파이프는 가로 모양 파이프

	DFS(sy, sx+1, dir);	// dir: 0 가로, 1 세로, 2 대각선

	return;
}

int main() {
	std::cin >> N;

	// 도착지 설정
	dy = N - 1;
	dx = N - 1;

	// 지도 정보 입력
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			std::cin >> MAP[j][i];
		}
	}
	sol();
	std::cout << ans;

	return 0;
}