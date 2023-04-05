#include <iostream>
#include <algorithm>

int N, M;	// N: 행렬의 행의 크기, M: 행렬의 열의 크기
int DP[1002][1002][3];	// DP[i][j][k]: i행 j열을 k 방향으로 왔을 때의 최소 연료 소모
int MAP[1001][1001];	// MAP[i][j]: i행 j열로 갈 때 소모되는 연료의 양
int ans = 21e8;	// ans: 달 여행에 필요한 최소 연료의 값

int dir[] = { -1, 0, 1 };	// dir[i]: i 방향 (0: 왼쪽, 1: 그대로, 2: 오른쪽)

void sol() {
	for (int j = 0; j < N + 1; j++) {	// DP[N]은 달에 도착할 때 까지 소모된 최소 연료
		for (int i = 0; i < M; i++) {
			for (int d = 0; d < 3; d++) {
				DP[j][i][d] = 21e8;	// 최소값으로 갱신하기 위해 최대값 넣음
			}
		}
	}

	for (int i = 0; i < M; i++) {
		for (int d = 0; d < 3; d++) {
			DP[0][i][d] = MAP[0][i];	// 지구에서 첫 번째 공간은 방향에 상관 없음
		}
	}


	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++) {
			for (int d = 0; d < 3; d++) {
				int y = j + 1;	// y: 무조건 아래로 내려감
				int x = i + dir[d];	// x: 이동할 곳				
				int distance;	// distance: 최소 연료 소모

				if (x < 0 || x >= M) continue;	// 범위 벗어나면 continue	

				if (d == 0) {	// 왼쪽 아래로 이동
					distance = std::min(DP[j][i][1], DP[j][i][2]);	//0 방향으로 갈수 있는 후보 중 최소 값
				}
				if (d == 1) {	// 바로 아래로 이동
					distance = std::min(DP[j][i][0], DP[j][i][2]);	// 1 방향으로 갈수 있는 후보 중 최소 값
				}
				if (d == 2) {	// 오른쪽 아래로 이동
					distance = std::min(DP[j][i][0], DP[j][i][1]);	// 2 방향으로 갈수 있는 후보 중 최소 값
				}
				DP[y][x][d] = std::min(DP[y][x][d], distance + MAP[y][x]);	// 값 갱신
			}
		}
	}
	for (int i = 0; i < M; i++) {
		for (int d = 0; d < 3; d++) {
			ans = std::min(ans, DP[N][i][d]);	// DP[N]은 달
		}
	}

	return;
}

void input() {
	std::cin >> N >> M;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++) {
			std::cin >> MAP[j][i];	// 연료 소모양
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