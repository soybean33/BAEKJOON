#include <iostream>
#include <queue>
#include <algorithm>

struct Coordinate {	// 좌표
	int z, y, x;
};

int M, N, H;	// M: 상자의 가로 칸 수, N: 상자의 세로 칸 수, H: 쌓아올려지는 상자의 수
int BOX[101][101][101];	// BOX[i][j][k]: i 번째 상자의 j 행 k 열의 토마토 정보 -> 익은 토마토 1, 익지 않은 토마토 0, 토마토가 들어있지 않은 칸 -1
int visited[101][101][101];	// visited[i][j][k]: i 번째 상자의 j행 k 열의 토마토가 익은 최소 일수

std::queue<Coordinate> q;	// q: 토마토가 익도록 영향을 미칠 토마토의 좌표
int tomatoCnt = 0;	// tomatoCnt: 익지 않은 토마토의 개수
int days = 0;	// days: 토마토가 다 익게 되는 날짜

// 방향벡터: 위 아래 왼쪽 오른쪽 앞 뒤
int dirZ[6] = { 1, -1, 0, 0, 0, 0 };
int dirY[6] = { 0, 0, 0, 0, -1, 1 };
int dirX[6] = { 0, 0, -1, 1, 0, 0 };

void sol() {

	while (!q.empty()) {
		Coordinate cur = q.front();	// cur: 영향을 미칠 토마토의 좌표
		q.pop();

		for (int dir = 0; dir < 6; dir++) {
			Coordinate next = { cur.z + dirZ[dir], cur.y + dirY[dir], cur.x + dirX[dir] };	// next: 익을 토마토

			// 범위 벗어나면 continue
			if (next.z < 0 || next.z >= H) continue;
			if (next.y < 0 || next.y >= N) continue;
			if (next.x < 0 || next.x >= M) continue;

			if (BOX[next.z][next.y][next.x] == -1 || BOX[next.z][next.y][next.x] == 1) continue;	// 토마토가 없거나 이미 익은 토마토면 continue
			if (visited[next.z][next.y][next.x] != 0) continue;	// 익지 않았다가 익은 토마토가 있는 위치 continue

			visited[next.z][next.y][next.x] = visited[cur.z][cur.y][cur.x] + 1;	// 토마토가 익은 일수 계산
			
			--tomatoCnt;	// 익지 않은 토마토 감소

			if (tomatoCnt == 0) {	// 익지 않은 토마토 없음
				days = visited[next.z][next.y][next.x];
				return;
			}

			q.push(next);
		}
	}

	return;
}

void input() {

	std::cin >> M >> N >> H;

	for (int k = 0; k < H; k++) {
		for (int j = 0; j < N; j++) {
			for (int i = 0; i < M; i++) {
				std::cin >> BOX[k][j][i];
				if (BOX[k][j][i] == 0) ++tomatoCnt;	// 익지 않은 토마토
				else if (BOX[k][j][i] == 1) { 	// 익은 토마토
					q.push({ k, j, i });
					visited[k][j][i] = 1;
				}
			}
		}
	}

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	if (tomatoCnt == 0) {	// 익지 않은 토마토가 없는 경우
		std::cout << 0;	// 0 일 소요
		return 0;
	}

	sol();

	if (tomatoCnt == 0) std::cout << days - 1;	// 1 부터 시작하였으므로 -1
	else std::cout << -1;	// 토마토가 모두 익지는 못하는 상황 -1

	return 0;
}