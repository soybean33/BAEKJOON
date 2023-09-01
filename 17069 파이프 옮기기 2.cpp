#include <iostream>
#include <vector>

long long Solution(const int& N, const std::vector<std::vector<bool>>& MAP) {

	long long answer = 0;	// answer: 파이프의 한쪽 끝을 (N, N)으로 이동시키는 방법의 수

	std::vector<std::vector<std::vector<long long>>> DP;	// DP[i][j][k]: i 행 j 열에 k 파이프 모양으로 이동하는 방법의 수

	DP.assign(N + 1, std::vector<std::vector<long long>>(N + 1, std::vector<long long>(3, 0)));

	DP[0][1][0] = 1;	// 가장 처음의 파이프는 (1,1)와 (1,2)를 차지하고 있음

	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			if (y == 0 && x == 0) continue;	// (0, 0)은 파이프가 올 수 없음
			if (MAP[y][x]) continue;	// 벽이 있는 경우 continue

			if (!MAP[y][x + 1]) DP[y][x + 1][0] = DP[y][x][2] + DP[y][x][0];	// 오른쪽 방향을 향하는 파이프를 설치할 수 있는 방법의 수 -> 대각선 방향 파이프 방법 수 + 오른쪽 방향 파이프 방법 수
			if (!MAP[y + 1][x]) DP[y + 1][x][1] = DP[y][x][2] + DP[y][x][1];	// 아래 방향을 향하는 파이프를 설치할 수 있는 방법의 수 -> 대각선 방향 파이프 방법 수 + 아래 방향 파이프 방법 수
			if (y + 1 < N && x + 1 < N) {
				if(!MAP[y+1][x] && !MAP[y][x+1] && !MAP[y+1][x+1]) DP[y + 1][x + 1][2] = DP[y][x][0] + DP[y][x][1] + DP[y][x][2];	// 대각 선 방향을 향하는 파이프를 설치할 수 있는 방법의 수 -> 오른쪽, 아래, 대각선 방향 파이의 방법 수 모두를 더함
			}
		}
	}
	
	answer = DP[N - 1][N - 1][0] + DP[N - 1][N - 1][1] + DP[N - 1][N - 1][2];	// (N, N)의 방법의 수를 모두 더함

	return answer;
}

void Input(int& N, std::vector<std::vector<bool>>& MAP) {

	std::cin >> N;

	MAP.assign(N + 1, std::vector<bool>(N + 1, true));

	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			int wall;	// wall: 벽
			std::cin >> wall;

			MAP[y][x] = wall == 1 ? true : false;	// 벽이 있다면 true, 없다면 false
		}
	}

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;	// N: 새 집의 크기의 한 변의 길이
	std::vector<std::vector<bool>> MAP;	// MAP[i][j]: i 행 j 열의 벽의 유무 -> false: 빈 칸, true: 벽

	Input(N, MAP);

	std::cout << Solution(N, MAP);

	return 0;
}