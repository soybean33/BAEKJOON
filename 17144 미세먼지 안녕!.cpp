#include <iostream>

struct Coordinate {	// 좌표
	int y, x;
};

int R, C, T;	// R: 방의 세로 크기, C: 방의 가로 크기, T: 시간
int room[51][51];	// room[i][j]: i행 j열의 정보
Coordinate airCleaner;	// airCleaner: 공기 청정기의 위치 -> 아래쪽 좌표 저장
int ans;	// ans: 남아있는 미세먼지의 양


// 방향 벡터
int dirY[] = { 0,1,0,-1 };
int dirX[] = { 1,0,-1,0 };

void sol() {
	for (int t = 0; t < T; t++) {
		// 미세먼지 확산 시작
		int diffusion[51][51] = { 0, };	// diffusion[i][j]: i행 j열에 확산된 먼지
		for (int j = 0; j < R; j++) {
			for (int i = 0; i < C; i++) {
				if (room[j][i] <= 0) continue;	// 공기청정기(-1)이거나 먼지가 없으면(0) continue

				int num = 0;	// num: 확산된 방향의 개수
				for (int dir = 0; dir < 4; dir++) {
					int newY = j + dirY[dir];
					int newX = i + dirX[dir];

					if (newY < 0 || newX < 0 || newY >= R || newX >= C) continue;	// 범위 벗어나면 continue

					if (room[newY][newX] == -1) continue;	// 공기 청정기가 있는 곳이면 continue

					num++;
					diffusion[newY][newX] += room[j][i] / 5;	// 확산되는 양은 A/5
				}

				room[j][i] = room[j][i] - (room[j][i] / 5) * num;	// 남은 미세먼지의 양은 A - (A/5) * 확산된 방향의 개수 
			}
		}
		for (int j = 0; j < R; j++) {	// 확산된 먼지 더하기
			for (int i = 0; i < C; i++) {
				room[j][i] += diffusion[j][i];
			}
		}
		// 미세먼지 확산 종료

		// 공기 청정기 작동
		// 위쪽 반시계
		Coordinate air = { airCleaner.y - 1, airCleaner.x };	// 위쪽 공기 청정기
		for (int j = air.y - 1; j > 0; j--) {	// 왼쪽
			room[j][0] = room[j - 1][0];
		}
		for (int i = 1; i < C; i++) {	// 위쪽
			room[0][i - 1] = room[0][i];
		}
		for (int j = 1; j < air.y + 1; j++) {	// 오른쪽
			room[j - 1][C - 1] = room[j][C - 1];
		}
		for (int i = C - 1; i > 0; i--) {	// 아래쪽
			room[air.y][i] = room[air.y][i - 1];
		}
		room[air.y][1] = 0;
		room[air.y][0] = -1;

		// 아래쪽 시계
		air = { airCleaner.y, airCleaner.x };	// 아래쪽 공기 청정기
		for (int j = air.y + 1; j < R; j++) {	// 왼쪽
			room[j - 1][0] = room[j][0];
		}
		for (int i = 1; i < C; i++) {	// 아래쪽
			room[R - 1][i - 1] = room[R - 1][i];
		}
		for (int j = R - 1; j > air.y; j--) {	// 오른쪽
			room[j][C - 1] = room[j - 1][C - 1];
		}
		for (int i = C - 1; i > 0; i--) {	// 위쪽
			room[air.y][i] = room[air.y][i-1];
		}
		room[air.y][1] = 0;
		room[air.y][0] = -1;
		int pa = 1;
	}	

	for (int j = 0; j < R; j++) {
		for (int i = 0; i < C; i++) {			
			if (room[j][i] == 0 || room[j][i] == - 1) continue;	// 먼지가 없거나, 공기청정기가 있는 칸은 continue

			ans += room[j][i];
		}
	}
}

void input() {
	std::cin >> R >> C >> T;
	for (int j = 0; j < R; j++) {
		for (int i = 0; i < C; i++) {
			std::cin >> room[j][i];
			if (room[j][i] == -1)
				airCleaner = {j, i};
		}
	}

}

int main() {
	input();
	sol();
	std::cout << ans;
	return 0;
}