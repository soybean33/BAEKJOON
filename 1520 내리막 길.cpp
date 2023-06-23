#include <iostream>
#include <cstring>

int M, N;	// M: 세로의 크기, N: 가로의 크기
int MAP[500][500];	// MAP[i][j]: i 행 j 열의 높이
int dp[500][500];	// dp[i][j]: i 행 j 열에 갈 수 있는 경로의 수
int ans;	// 이동 가능한 경로의 수

// 방향 벡터
int dirY[] = {0, 1, 0, -1};
int dirX[] = {1, 0, -1, 0};

int dfs(int y, int x){	// y, x: 현재 위치 좌표

	if(y == M - 1 && x == N - 1) return 1;	// 도착지점 1 return
	if(dp[y][x] != -1) return dp[y][x];	// 이미 방문한 적이 있으면 기록했던 값을 return

	dp[y][x] = 0;	// 방문 하였으므로 0으로 초기화

	for(int dir=0; dir<4; dir++){	// 4가지 방향으로 탐색
		// nextY, nextX: 이동 좌표
		int nextY = y + dirY[dir];
		int nextX = x + dirX[dir];

		if(nextY < 0 || nextX < 0 || nextY >= M || nextX >= N) continue;	// 범위 벗어나면 continue

		if(MAP[y][x] > MAP[nextY][nextX]){	// 내리막길
			dp[y][x] = dp[y][x] + dfs(nextY, nextX);	// 기록한 가능한 길 + 다음에 갈 수 있는 길의 경로 수
		}
	}

	return dp[y][x];	// (y, x) 까지 갈 수 있는 경로의 수 return
}

void solution(){

	memset(dp, -1, sizeof(dp));	// 가지 않은 곳은 -1로 초기화

	ans = dfs(0, 0);	// (0, 0) 부터 탐색 시작

	return;
}

void input(){

	std::cin >> M >> N;

	for(int j=0; j<M; j++){
		for(int i=0; i<N; i++){
			std::cin >> MAP[j][i];
		}
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	solution();

	std::cout << ans;

	return 0;
}